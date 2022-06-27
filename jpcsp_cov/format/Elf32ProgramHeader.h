#pragma once

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
	using namespace jpcsp::filesystems;
	using namespace jpcsp::util;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;

	class Elf32ProgramHeader
	{

	private:
		long long p_type = 0;
		long long p_offset = 0;
		long long p_vaddr = 0;
		long long p_paddr = 0;
		long long p_filesz = 0;
		long long p_memsz = 0;
		long long p_flags = 0; // Bits: 0x1=executable, 0x2=writable, 0x4=readable, demo PRX's were found to be not writable
		long long p_align = 0;

		static int sizeof_Keyword();

	public:
		Elf32ProgramHeader(ByteBuffer *f);

	private:
		void read(ByteBuffer *f);

	public:
		virtual std::string toString();

		virtual long long getP_type();

		virtual long long getP_offset();

		virtual long long getP_vaddr();

		virtual long long getP_paddr();

		virtual long long getP_filesz();

		virtual long long getP_memsz();

		virtual long long getP_flags();

		virtual long long getP_align();
	};

}
