#pragma once

#include "../Memory.h"

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

	/**
	 * http://psp.jim.sh/pspsdk-doc/structScePspDateTime.html
	 * http://psp.jim.sh/pspsdk-doc/structpspTime.html */
	class ScePspDateTime
	{
	public:
		int year = 0;
		int month = 0;
		int day = 0;
		int hour = 0;
		int minute = 0;
		int second = 0;
		int microsecond = 0;

		/** @param time Unix time, seconds since the epoch/1970. */
		ScePspDateTime(long long time);

		/** All fields will be initialised to the time the object was created. */
		ScePspDateTime();

		ScePspDateTime(int year, int month, int day, int hour, int minute, int second, int microsecond);

		virtual void read(Memory *mem, int address);

		virtual void write(Memory *mem, int address);

		static int sizeof_Keyword();
	};

}
