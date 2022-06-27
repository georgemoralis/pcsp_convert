using namespace std;

#include "pspstdio.h"

namespace jpcsp::HLE
{
	using Emulator = jpcsp::Emulator;
pspstdio *pspstdio::instance;

	pspstdio *pspstdio::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new pspstdio();
		}
		return instance;
	}

	void pspstdio::sceKernelStdin()
	{
		Emulator::getProcessor()->gpr[2] = 3; //not sure if it returns okay but seems so
	}

	void pspstdio::sceKernelStdout()
	{
		Emulator::getProcessor()->gpr[2] = 1; //not sure if it returns okay but seems so
	}

	void pspstdio::sceKernelStderr()
	{
		Emulator::getProcessor()->gpr[2] = 2; //not sure if it returns okay but seems so
	}
}
