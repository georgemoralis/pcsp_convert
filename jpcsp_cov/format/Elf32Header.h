#pragma once

#include "../MemoryMap.h"
#include "../util/Utilities.h"
#include <string>
#include "../stringbuilder.h"

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
namespace jpcsp::format
{

	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using namespace jpcsp::util;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;

	class Elf32Header
	{


	private:
		long long e_magic = 0;
		int e_class = 0;
		int e_data = 0;
		int e_idver = 0;
		signed char *e_pad = new signed char[9];
		int e_type = 0;
		int e_machine = 0;
		long long e_version = 0;
		long long e_entry = 0;
		long long e_phoff = 0;
		long long e_shoff = 0;
		long long e_flags = 0;
		int e_ehsize = 0;
		int e_phentsize = 0;
		int e_phnum = 0;
		int e_shentsize = 0;
		int e_shnum = 0;
		int e_shstrndx = 0;

	public:
		virtual ~Elf32Header()
		{
			delete[] e_pad;
		}

	private:
		void read(ByteBuffer *f);


	 public:
		 Elf32Header(ByteBuffer *f);

		 virtual bool isValid();

		 virtual bool isMIPSExecutable();

		 virtual bool isPRXDetected();

		 virtual bool requiresRelocation();

		virtual std::string toString();

		virtual long long getE_magic();

		virtual int getE_class();

		virtual int getE_data();

		virtual int getE_idver();

		virtual signed char *getE_pad();

		virtual int getE_type();

		virtual int getE_machine();

		virtual long long getE_version();

		virtual long long getE_entry();

		virtual long long getE_phoff();

		virtual long long getE_shoff();

		virtual long long getE_flags();

		virtual int getE_ehsize();

		virtual int getE_phentsize();

		virtual int getE_phnum();

		virtual int getE_shentsize();

		virtual int getE_shnum();

		virtual int getE_shstrndx();
	};

}
