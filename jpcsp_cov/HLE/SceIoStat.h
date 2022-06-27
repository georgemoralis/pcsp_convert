#pragma once

#include "../Memory.h"
#include "ScePspDateTime.h"

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

	using Memory = jpcsp::Memory;

	/** http://psp.jim.sh/pspsdk-doc/structSceIoStat.html */
	class SceIoStat
	{
	public:
		int mode = 0; // permissions?
		int attr = 0; // ?
		long long size = 0;
		ScePspDateTime *ctime;
		ScePspDateTime *atime;
		ScePspDateTime *mtime;

		virtual ~SceIoStat()
		{
			delete ctime;
			delete atime;
			delete mtime;
		}

		SceIoStat(int mode, int attr, long long size, ScePspDateTime *ctime, ScePspDateTime *atime, ScePspDateTime *mtime);

		virtual void write(Memory *mem, int address);

		static int sizeof_Keyword();
	};

}
