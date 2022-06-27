using namespace std;

#include "LoadExec.h"

namespace jpcsp::HLE
{
	using Emulator = jpcsp::Emulator;
LoadExec *LoadExec::instance;

	LoadExec *LoadExec::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new LoadExec();
		}
		return instance;
	}

	LoadExec::LoadExec()
	{
	}

	void LoadExec::sceKernelRegisterExitCallback(int a0)
	{
		// TODO
		cout << "sceKernelRegisterExitCallback unimplemented" << endl;

		// Fake successful return
		Emulator::getProcessor()->gpr[2] = 0;
	}

	void LoadExec::sceKernelExitGame()
	{
		cout << "Program exit detected (sceKernelExitGame)" << endl;
		Emulator::PauseEmu();
	}
}
