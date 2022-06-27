using namespace std;

#include "pspge.h"
#include "pspdisplay.h"

namespace jpcsp::HLE
{
	using Emulator = jpcsp::Emulator;
	using MemoryMap = jpcsp::MemoryMap;
	using DisplayList = jpcsp::graphics::DisplayList;
	using VideoEngine = jpcsp::graphics::VideoEngine;
pspge *pspge::instance;

	pspge *pspge::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new pspge();
		}
		return instance;
	}

	pspge::pspge()
	{
	}

	void pspge::Initialise()
	{
		DisplayList::Lock();
		DisplayList::Initialise();
		DisplayList::Unlock();
	}

	void pspge::sceGeEdramGetAddr()
	{
		Emulator::getProcessor()->gpr[2] = MemoryMap::START_VRAM;
	}

	void pspge::sceGeListEnQueue(int list, int stall, int callbackId, int argument)
	{
		DisplayList::Lock();

		/*
		list 	- The head of the list to queue.
		stall 	- The stall address. If NULL then no stall address set and the list is transferred immediately.
		cbid 	- ID of the callback set by calling sceGeSetCallback
		arg 	- Probably a parameter to the callbacks (to be confirmed)
		*/

		// remove uncache bit
		list &= 0x3fffffff;
		stall &= 0x3fffffff;

		DisplayList *displayList = new DisplayList(list, stall, callbackId, argument);
		DisplayList::addDisplayList(displayList);
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
		log("The list " + displayList->toString());

		if (displayList->status == DisplayList::QUEUED)
		{
			pspdisplay::get_instance()->setDirty(true);
		}

		Emulator::getProcessor()->gpr[2] = displayList->id;
		DisplayList::Unlock();

//JAVA TO C++ CONVERTER TODO TASK: A 'delete displayList' statement was not added since displayList was passed to a method or constructor. Handle memory management manually.
	}

	void pspge::sceGeListDeQueue(int qid)
	{
		DisplayList::Lock();
		// TODO if we render asynchronously, using another thread then we need to interupt it first
		if (DisplayList::removeDisplayList(qid))
		{
			log("sceGeListDeQueue qid=" + to_string(qid));
			Emulator::getProcessor()->gpr[2] = 0;
		}
		else
		{
			log("sceGeListDeQueue failed qid=" + to_string(qid));
			Emulator::getProcessor()->gpr[2] = -1;
		}
		DisplayList::Unlock();
	}

	void pspge::sceGeListUpdateStallAddr(int qid, int stallAddress)
	{
		DisplayList::Lock();
		DisplayList *displayList = DisplayList::getDisplayList(qid);
		if (displayList != nullptr)
		{
			// remove uncache bit
			stallAddress &= 0x3fffffff;

			log("sceGeListUpdateStallAddr qid=" + to_string(qid) + " new stall addr " + String::format("%08x", stallAddress) + " " + to_string((stallAddress - displayList->stallAddress) / 4) + " new commands");

			displayList->stallAddress = stallAddress;
			if (displayList->pc != displayList->stallAddress)
			{
				displayList->status = DisplayList::QUEUED;
				pspdisplay::get_instance()->setDirty(true);
			}

			Emulator::getProcessor()->gpr[2] = 0;
		}
		else
		{
			log("sceGeListUpdateStallAddr qid=" + to_string(qid) + " failed, no longer exists");
			Emulator::getProcessor()->gpr[2] = -1;
		}
		DisplayList::Unlock();
	}

	void pspge::log(const string &msg)
	{
		cout << "sceGe DEBUG > " << msg << endl;
	}
}
