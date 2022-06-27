using namespace std;

#include "pspctrl.h"

namespace jpcsp::HLE
{
	using Emulator = jpcsp::Emulator;
	using Memory = jpcsp::Memory;
pspctrl *pspctrl::instance;

	pspctrl *pspctrl::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new pspctrl();
		}
		return instance;
	}

	pspctrl::pspctrl()
	{
	}

	void pspctrl::setButtons(signed char Lx, signed char Ly, int Buttons, bool pressed)
	{
		this->Lx = Lx;
		this->Ly = Ly;
		this->Buttons = Buttons;

		if (pressed)
		{
			this->uiRelease = 0;
			this->uiPress = 1;
		}
		else
		{
			this->uiRelease = 1;
			this->uiPress = 0;
		}
	}

	bool pspctrl::isModeDigital()
	{
		if (mode == 0)
		{
			return true;
		}
		return false;
	}

	void pspctrl::sceCtrlSetSamplingCycle(int a0)
	{
		Emulator::getProcessor()->gpr[2] = cycle;
		cycle = a0;
	}

	void pspctrl::sceCtrlGetSamplingCycle(int a0)
	{
		Memory::get_instance()->write32(a0, cycle);
		Emulator::getProcessor()->gpr[2] = 0;
	}

	void pspctrl::sceCtrlSetSamplingMode(int a0)
	{
		Emulator::getProcessor()->gpr[2] = mode;
		mode = a0;
	}

	void pspctrl::sceCtrlGetSamplingMode(int a0)
	{
		Memory::get_instance()->write32(a0, mode);
		Emulator::getProcessor()->gpr[2] = 0;
	}

	void pspctrl::sceCtrlPeekBufferPositive(int a0, int a1)
	{
		Memory *mem = Memory::get_instance();
		int i;

		for (i = 0; i < a1; i++)
		{
			// TODO set timestamp, get buttons and analog state, probably from jpcsp.Controller class
			int TimeStamp = 0;

			mem->write32(a0, TimeStamp);
			mem->write32(a0 + 4, Buttons);
			mem->write8(a0 + 8, Lx);
			mem->write8(a0 + 9, Ly);
			a0 += 16;
		}

		Emulator::getProcessor()->gpr[2] = i;
	}

	void pspctrl::sceCtrlPeekBufferNegative(int a0, int a1)
	{
		Memory *mem = Memory::get_instance();
		int i;

		for (i = 0; i < a1; i++)
		{
			// TODO set timestamp, get buttons and analog state
			int TimeStamp = 0;

			mem->write32(a0, TimeStamp);
			mem->write32(a0 + 4, ~Buttons);
			mem->write8(a0 + 8, Lx);
			mem->write8(a0 + 9, Ly);
			a0 += 16;
		}

		Emulator::getProcessor()->gpr[2] = i;
	}

	void pspctrl::sceCtrlReadBufferPositive(int a0, int a1)
	{
		Memory *mem = Memory::get_instance();
		int i;

		for (i = 0; i < a1; i++)
		{
			// TODO set timestamp, get buttons and analog state
			int TimeStamp = 0;

			mem->write32(a0, TimeStamp);
			mem->write32(a0 + 4, Buttons);
			mem->write8(a0 + 8, Lx);
			mem->write8(a0 + 9, Ly);
			a0 += 16;
		}

		Emulator::getProcessor()->gpr[2] = i;
	}

	void pspctrl::sceCtrlReadBufferNegative(int a0, int a1)
	{
		Memory *mem = Memory::get_instance();
		int i;

		for (i = 0; i < a1; i++)
		{
			// TODO set timestamp, get buttons and analog state
			int TimeStamp = 0;

			mem->write32(a0, TimeStamp);
			mem->write32(a0 + 4, ~Buttons);
			mem->write8(a0 + 8, Lx);
			mem->write8(a0 + 9, Ly);
			a0 += 16;
		}

		Emulator::getProcessor()->gpr[2] = i;
	}

	void pspctrl::sceCtrlPeekLatch(int a0)
	{
		Memory *mem = Memory::get_instance();

		mem->write32(a0, 0); //uiMake
		mem->write32(a0 + 4, 0); //uiBreak
		mem->write32(a0 + 8, uiPress);
		mem->write32(a0 + 12, uiRelease);
		Emulator::getProcessor()->gpr[2] = 0;
	}

	pspctrl::SceCtrlData::SceCtrlData(pspctrl *outerInstance, int TimeStamp, int Buttons, signed char Lx, signed char Ly) : outerInstance(outerInstance)
	{
		this->TimeStamp = TimeStamp;
		this->Buttons = Buttons;
		this->Lx = Lx;
		this->Ly = Ly;
		// no use allocating this
		//Rsrv = new byte[6];
	}

	void pspctrl::SceCtrlData::write(Memory *mem, int address)
	{
		mem->write32(address, TimeStamp);
		mem->write32(address + 4, Buttons);
		mem->write8(address + 8, Lx);
		mem->write8(address + 9, Ly);
		// leaving Rsrv uninitialised
	}

	int pspctrl::SceCtrlData::sizeof_Keyword()
	{
		return 16;
	}
}
