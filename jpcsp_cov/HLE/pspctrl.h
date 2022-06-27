#pragma once

#include "../Emulator.h"
#include "../Memory.h"

/*
Function:
- HLE everything in http://psp.jim.sh/pspsdk-doc/pspctrl_8h.html


This file is part of jpcsp.

Jpcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Jpcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Jpcsp.  If not, see <http://www.gnu.org/licenses/>.
 */
namespace jpcsp::HLE
{

	using Memory = jpcsp::Memory;

	class pspctrl
	{
	private:
		static pspctrl *instance;

		int cycle = 0;
		int mode = 0; // PspCtrlMode { PSP_CTRL_MODE_DIGITAL = 0, PSP_CTRL_MODE_ANALOG  }
		int uiPress = 0;
		int uiRelease = 1;

		signed char Lx = 0;
		signed char Ly = 0;
		int Buttons = 0;

	public:
		static constexpr int PSP_CTRL_SELECT = 0x000001;
		static constexpr int PSP_CTRL_START = 0x000008;
		static constexpr int PSP_CTRL_UP = 0x000010;
		static constexpr int PSP_CTRL_RIGHT = 0x000020;
		static constexpr int PSP_CTRL_DOWN = 0x000040;
		static constexpr int PSP_CTRL_LEFT = 0x000080;
		static constexpr int PSP_CTRL_LTRIGGER = 0x000100;
		static constexpr int PSP_CTRL_RTRIGGER = 0x000200;
		static constexpr int PSP_CTRL_TRIANGLE = 0x001000;
		static constexpr int PSP_CTRL_CIRCLE = 0x002000;
		static constexpr int PSP_CTRL_CROSS = 0x004000;
		static constexpr int PSP_CTRL_SQUARE = 0x008000;
		static constexpr int PSP_CTRL_HOME = 0x010000;
		static constexpr int PSP_CTRL_HOLD = 0x020000;
		static constexpr int PSP_CTRL_NOTE = 0x800000;
		static constexpr int PSP_CTRL_SCREEN = 0x400000;
		static constexpr int PSP_CTRL_VOLUP = 0x100000;
		static constexpr int PSP_CTRL_VOLDOWN = 0x200000;
		static constexpr int PSP_CTRL_WLAN_UP = 0x040000;
		static constexpr int PSP_CTRL_REMOTE = 0x080000;
		static constexpr int PSP_CTRL_DISC = 0x1000000;
		static constexpr int PSP_CTRL_MS = 0x2000000;

		static pspctrl *get_instance();

	private:
		pspctrl();

	public:
		virtual void setButtons(signed char Lx, signed char Ly, int Buttons, bool pressed);

		virtual bool isModeDigital();

		virtual void sceCtrlSetSamplingCycle(int a0);

		virtual void sceCtrlGetSamplingCycle(int a0);

		virtual void sceCtrlSetSamplingMode(int a0);

		virtual void sceCtrlGetSamplingMode(int a0);

		virtual void sceCtrlPeekBufferPositive(int a0, int a1);

		virtual void sceCtrlPeekBufferNegative(int a0, int a1);

		virtual void sceCtrlReadBufferPositive(int a0, int a1);

		virtual void sceCtrlReadBufferNegative(int a0, int a1);

		virtual void sceCtrlPeekLatch(int a0);

	private:
		class SceCtrlData
		{
		private:
			pspctrl *outerInstance;

			int TimeStamp = 0;
			int Buttons = 0;
			signed char Lx = 0;
			signed char Ly = 0;
			signed char *Rsrv; // 6 bytes

		public:
			virtual ~SceCtrlData()
			{
				delete[] Rsrv;
				delete outerInstance;
			}

		private:
			SceCtrlData(pspctrl *outerInstance, int TimeStamp, int Buttons, signed char Lx, signed char Ly);

			void write(Memory *mem, int address);

		public:
			virtual int sizeof_Keyword();
		};
	};

}
