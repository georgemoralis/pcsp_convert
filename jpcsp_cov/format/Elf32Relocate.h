#pragma once

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

	using namespace jpcsp::util;
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;

	class Elf32Relocate
	{

	private:
		long long r_offset = 0;
		long long r_info = 0;

	public:
		static int sizeof_Keyword();

		virtual void read(ByteBuffer *f);

		virtual std::string toString();

		virtual long long getR_offset();

		virtual void setR_offset(long long r_offset);

		virtual long long getR_info();

		virtual void setR_info(long long r_info);
	};

}
