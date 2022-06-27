#pragma once

#include "../Emulator.h"
#include <iostream>

/*
Function:
- HLE everything in http://psp.jim.sh/pspsdk-doc/group__LoadExec.html


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


	class LoadExec
	{
	private:
		static LoadExec *instance;

	public:
		static LoadExec *get_instance();

	private:
		LoadExec();

	public:
		virtual void sceKernelRegisterExitCallback(int a0);

		virtual void sceKernelExitGame();

		/* TODO
		public void sceKernelLoadExec(int a0, int a1)
		{
		    Emulator.getProcessor().gpr[2] = 0;
		}
		*/
	};

}
