using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "ThreadMan.h"
#include "../AllegrexOpcodes.h"
#include "pspSysMem.h"
#include "SceUIDMan.h"
#include "../util/Utilities.h"

namespace jpcsp::HLE
{
	using Collection = java::util::Collection;
	using Collections = java::util::Collections;
	using Comparator = java::util::Comparator;
	using HashMap = java::util::HashMap;
	using Iterator = java::util::Iterator;
	using LinkedList = java::util::LinkedList;
	using List = java::util::List;
	using Emulator = jpcsp::Emulator;
	using GeneralJpcspException = jpcsp::GeneralJpcspException;
	using Memory = jpcsp::Memory;
	using MemoryMap = jpcsp::MemoryMap;
	using Processor = jpcsp::Processor;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;
ThreadMan *ThreadMan::instance;
unordered_map<int, SceKernelThreadInfo*> ThreadMan::threadlist;

	ThreadMan *ThreadMan::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new ThreadMan();
		}
		return instance;
	}

	ThreadMan::ThreadMan()
	{
	}

	void ThreadMan::Initialise(int entry_addr, int attr)
	{
		//System.out.println("ThreadMan: Initialise");

		threadlist = unordered_map<int, SceKernelThreadInfo*>();

		// Clear stack allocation info MOVED TO PSPSYSMEM
		//stackAllocated = 0;

		install_idle_threads();

		current_thread = new SceKernelThreadInfo(this, "root", entry_addr, 0x20, 0x40000, attr);

		// Set user mode bit if kernel mode bit is not present
		if ((current_thread->attr & PSP_THREAD_ATTR_KERNEL) != PSP_THREAD_ATTR_KERNEL)
		{
			current_thread->attr |= PSP_THREAD_ATTR_USER;
		}

		// Switch in this thread
		current_thread->status = PspThreadStatus::PSP_THREAD_RUNNING;
		current_thread->restoreContext();
	}

	void ThreadMan::install_idle_threads()
	{
		// Generate 2 idle threads which can toggle between each other when there are no ready threads
		int instruction_addiu = ((jpcsp::AllegrexOpcodes::ADDIU & 0x3f) << 26) | ((0 & 0x1f) << 21) | ((4 & 0x1f) << 16);
		int instruction_lui = ((jpcsp::AllegrexOpcodes::LUI & 0x3f) << 26) | ((31 & 0x1f) << 16) | (0x0800 & 0x0000ffff);
		int instruction_jr = ((jpcsp::AllegrexOpcodes::SPECIAL & 0x3f) << 26) | (jpcsp::AllegrexOpcodes::JR & 0x3f) | ((31 & 0x1f) << 21);
		int instruction_syscall = ((jpcsp::AllegrexOpcodes::SPECIAL & 0x3f) << 26) | (jpcsp::AllegrexOpcodes::SYSCALL & 0x3f) | ((0x201c & 0x000fffff) << 6);

		Memory::get_instance()->write32(MemoryMap::START_RAM + 0, instruction_addiu);
		Memory::get_instance()->write32(MemoryMap::START_RAM + 4, instruction_lui);
		Memory::get_instance()->write32(MemoryMap::START_RAM + 8, instruction_jr);
		Memory::get_instance()->write32(MemoryMap::START_RAM + 12, instruction_syscall);

		idle0 = new SceKernelThreadInfo(this, "idle0", MemoryMap::START_RAM, 0x7f, 0x0, 0x0);
		idle0->status = PspThreadStatus::PSP_THREAD_READY;

		idle1 = new SceKernelThreadInfo(this, "idle1", MemoryMap::START_RAM, 0x7f, 0x0, 0x0);
		idle1->status = PspThreadStatus::PSP_THREAD_READY;

		continuousIdleCycles = 0;
	}

	void ThreadMan::step()
	{
		if (current_thread != nullptr)
		{
			current_thread->runClocks++;

			//System.out.println("pc=" + Emulator.getProcessor().pc + " ra=" + Emulator.getProcessor().gpr[31]);

			// Hook jr ra to 0 (thread function returned)
			if (Emulator::getProcessor()->pc == 0 && Emulator::getProcessor()->gpr[31] == 0)
			{
				// Thread has exited
				cout << "Thread exit detected SceUID=" << Integer::toHexString(current_thread->uid) << " name:'" << current_thread->name << "' return:" << Emulator::getProcessor()->gpr[2] << endl;
				current_thread->exitStatus = Emulator::getProcessor()->gpr[2]; // v0
				current_thread->status = PspThreadStatus::PSP_THREAD_STOPPED;
				contextSwitch(nextThread());
			}

			// Watch dog timer
			if (current_thread == idle0 || current_thread == idle1)
			{
				continuousIdleCycles++;
				// TODO figure out a decent number of cycles to wait
				if (continuousIdleCycles > 1000)
				{
					cout << "Watch dog timer - pausing emulator" << endl;
					Emulator::PauseEmu();
				}
			}
			else
			{
				continuousIdleCycles = 0;
			}
		}
		else
		{
			// We always need to be in a thread! we shouldn't get here.
			cout << "No ready threads!" << endl;
		}

		Iterator<SceKernelThreadInfo*> it = threadlist.values().begin();
		while (it->hasNext())
		{
			SceKernelThreadInfo *thread = it->next();

			// Decrement delaysteps on sleeping threads
			if (thread->status == PspThreadStatus::PSP_THREAD_WAITING)
			{
				if (thread->delaysteps > 0)
				{
					thread->delaysteps--;
				}
				if (thread->delaysteps == 0)
				{
					thread->status = PspThreadStatus::PSP_THREAD_READY;
				}
			}

			// Cleanup stopped threads marked for deletion
			if (thread->status == PspThreadStatus::PSP_THREAD_STOPPED)
			{
				if (thread->do_delete)
				{
					// TODO cleanup thread, example: free the stack, anything else?
					// MemoryMan.free(thread.stack_addr);
					pspSysMem::get_instance()->free(thread->stack_addr);

					// Changed to thread safe iterator.remove
					//threadlist.remove(thread.uid);
					it->remove();
				 try
				 {
					SceUIDMan::get_instance()->releaseUid(thread->uid, "ThreadMan-thread");
				 }
				 catch (const runtime_error &e)
				 {
				   e.printStackTrace();
				 }
				}
			}
			it++;
		}

		// TODO watch dog timer?
	}

	void ThreadMan::contextSwitch(SceKernelThreadInfo *newthread)
	{
		if (current_thread != nullptr)
		{
			// Switch out old thread
			if (current_thread->status == PspThreadStatus::PSP_THREAD_RUNNING)
			{
				current_thread->status = PspThreadStatus::PSP_THREAD_READY;
			}
			// save registers
			current_thread->saveContext();

			/*
			System.out.println("saveContext SceUID=" + Integer.toHexString(current_thread.uid)
			    + " name:" + current_thread.name
			    + " PC:" + Integer.toHexString(current_thread.pcreg)
			    + " NPC:" + Integer.toHexString(current_thread.npcreg));
			*/
		}

		if (newthread != nullptr)
		{
			// Switch in new thread
			newthread->status = PspThreadStatus::PSP_THREAD_RUNNING;
			newthread->wakeupCount++; // check
			// restore registers
			newthread->restoreContext();

			//System.out.println("ThreadMan: switched to thread SceUID=" + Integer.toHexString(newthread.uid) + " name:'" + newthread.name + "'");
			/*
			System.out.println("restoreContext SceUID=" + Integer.toHexString(newthread.uid)
			    + " name:" + newthread.name
			    + " PC:" + Integer.toHexString(newthread.pcreg)
			    + " NPC:" + Integer.toHexString(newthread.npcreg));
			*/

			//Emulator.PauseEmu();
		}
		else
		{
			cout << "No ready threads - pausing emulator" << endl;
			Emulator::PauseEmu();
		}

		current_thread = newthread;
	}

	ThreadMan::SceKernelThreadInfo *ThreadMan::nextThread()
	{
		Collection<SceKernelThreadInfo*> *c;
		vector<SceKernelThreadInfo*> list;
		vector<SceKernelThreadInfo*>::const_iterator it;
		SceKernelThreadInfo *found = nullptr;

		// Find the thread with status PSP_THREAD_READY and the highest priority
		// In this implementation low priority threads can get starved
		c = threadlist.values();
		list = list<SceKernelThreadInfo*>(c);
//JAVA TO C++ CONVERTER TODO TASK: The 'Compare' parameter of std::sort produces a boolean value, while the Java Comparator parameter produces a tri-state result:
//ORIGINAL LINE: java.util.Collections.sort(list, idle0);
		sort(list.begin(), list.end(), idle0); // We need an instance of SceKernelThreadInfo for the comparator, so we use idle0
		it = list.begin();
		while (it != list.end())
		{

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
