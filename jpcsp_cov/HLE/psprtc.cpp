using namespace std;

#include "psprtc.h"
#include "ScePspDateTime.h"

namespace jpcsp::HLE
{
	using Calendar = java::util::Calendar;
	using Emulator = jpcsp::Emulator;
	using Memory = jpcsp::Memory;
psprtc *psprtc::instance;

	psprtc::psprtc()
	{
	}

	psprtc *psprtc::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new psprtc();
		}
		return instance;
	}

	void psprtc::sceRtcGetTickResolution()
	{
		/* 1000 ticks a second */
		Emulator::getProcessor()->gpr[2] = 1000;
	}

	void psprtc::sceRtcGetCurrentTick(int a0)
	{
		Memory::get_instance()->write64(a0, System::currentTimeMillis());
		Emulator::getProcessor()->gpr[2] = 0;
	}

	void psprtc::sceRtcGetCurrentClockLocalTime(int a0)
	{
		ScePspDateTime *pspTime = new ScePspDateTime();
		Memory *mem = Memory::get_instance();

		pspTime->write(mem, a0);

		Emulator::getProcessor()->gpr[2] = 0;

		delete pspTime;
	}
}
