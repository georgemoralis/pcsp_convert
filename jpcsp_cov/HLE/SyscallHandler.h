#pragma once

#include "../Emulator.h"
#include "../GeneralJpcspException.h"
#include <iostream>

/*
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

	using namespace jpcsp::Debugger::DisassemblerModule;

	class SyscallHandler
	{

		// Change this to return the number of cycles used?
	public:
		static void syscall(int code);
	};

}
