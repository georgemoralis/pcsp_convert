#pragma once

#include "../Memory.h"
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
	using Memory = jpcsp::Memory;
	using namespace jpcsp::util;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;

	class Elf32StubHeader
	{
		// Resolved version of s_modulename and in a Java String
	private:
		std::string s_modulenamez;

		long long s_modulename = 0;
		int s_version = 0;
		int s_flags = 0;
		int s_size = 0;
		int s_imports = 0;
		long long s_nid = 0;
		long long s_text = 0;

	public:
		static int sizeof_Keyword();
		Elf32StubHeader(ByteBuffer *f);

		Elf32StubHeader(Memory *mem, int address);

		virtual std::string toString();

		virtual std::string getModuleNamez();

		virtual void setModuleNamez(const std::string &moduleName);

		virtual long long getOffsetModuleName();

		virtual int getVersion();

		virtual int getFlags();

		virtual int getSize();

		/** The number of imports from this module */
		virtual int getImports();

		virtual long long getOffsetNid();

		virtual long long getOffsetText();
	};

}
