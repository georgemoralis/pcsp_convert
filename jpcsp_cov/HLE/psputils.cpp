using namespace std;

#include "psputils.h"

namespace jpcsp::HLE
{
	using Calendar = java::util::Calendar;
	using HashMap = java::util::HashMap;
	using Iterator = java::util::Iterator;
	using Random = java::util::Random;
	using Emulator = jpcsp::Emulator;
	using Memory = jpcsp::Memory;
	using Processor = jpcsp::Processor;
psputils *psputils::instance;

	psputils *psputils::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new psputils();
		}
		return instance;
	}

	psputils::psputils()
	{
	}

	void psputils::Initialise()
	{
		//System.out.println("Utils: Initialise");
		initialclocks = static_cast<int>(System::nanoTime()); // seconds * 1 million
		Mt19937List = unordered_map<int, SceKernelUtilsMt19937Context*>();
	}

	void psputils::sceKernelLibcTime(int time_t_addr)
	{
		long long millis = Calendar::getInstance().getTimeInMillis();
		int seconds = static_cast<int>(millis / 1000);
		if (time_t_addr != 0)
		{
			Memory::get_instance()->write32(time_t_addr, seconds);
		}
		Emulator::getProcessor()->gpr[2] = seconds;
	}

	void psputils::sceKernelLibcClock()
	{
		//int clocks = (int)System.nanoTime() - initialclocks; // seconds * 1 million
		currentClocks += 100; // FIXME: quick hack to fix NesterJ
		Emulator::getProcessor()->gpr[2] = currentClocks;
	}

	void psputils::sceKernelDcacheWritebackAll()
	{
		cout << "(Unimplement):sceKernelDcacheWritebackAll" << endl;
	}

	void psputils::sceKernelDcacheWritebackInvalidateAll()
	{
		cout << "(Unimplement):sceKernelDcacheWritebackInvalidateAll" << endl;
	}

	void psputils::sceKernelDcacheWritebackRange(int p_addr, int size)
	{
		cout << "(Unimplement):sceKernelDcacheWritebackRange" << endl;
	}

	void psputils::sceKernelDcacheWritebackInvalidateRange(int p_addr, int size)
	{
	   cout << "(Unimplement):sceKernelDcacheWritebackInvalidateRange" << endl;
	}

	void psputils::sceKernelDcacheInvalidateRange(int p_addr, int size)
	{
		cout << "(Unimplement):sceKernelDcacheInvalidateRange" << endl;
	}

	void psputils::sceKernelUtilsMt19937Init(int ctx_addr, int seed)
	{
		// We'll use the address of the ctx as a key
		Mt19937List.erase(ctx_addr); // Remove records of any already existing context at a0
		SceKernelUtilsMt19937Context tempVar(this, seed);
		Mt19937List.emplace(ctx_addr, &tempVar);

		// We'll overwrite all the context memory, 628 bytes
		Memory *mem = Memory::get_instance();
		for (int i = 0; i < 628; i += 4)
		{
			mem->write32(ctx_addr + i, 0xcdcdcdcd);
		}

		Emulator::getProcessor()->gpr[2] = 0;
	}

	void psputils::sceKernelUtilsMt19937UInt(int ctx_addr)
	{
		SceKernelUtilsMt19937Context *ctx = Mt19937List[ctx_addr];
		if (ctx != nullptr)
		{
			Emulator::getProcessor()->gpr[2] = ctx->r->nextInt();
		}
		else
		{
			// TODO what happens if the ctx is bad?
			cout << "sceKernelUtilsMt19937UInt uninitialised context " << Integer::toHexString(ctx_addr) << endl;
			Emulator::getProcessor()->gpr[2] = 0;
		}
	}

	psputils::SceKernelUtilsMt19937Context::SceKernelUtilsMt19937Context(psputils *outerInstance, int seed) : outerInstance(outerInstance)
	{
		r = new Random(seed);
	}
}
