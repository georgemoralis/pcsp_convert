#pragma once

#include "../filesystems/SeekableDataInput.h"
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
namespace jpcsp::util
{

	using IOException = java::io::IOException;
	using namespace jpcsp::filesystems;
	using ByteBuffer = java::nio::ByteBuffer;

	class Utilities
	{

	public:
		static std::string formatString(const std::string &type, const std::string &oldstring);

		static std::string integerToBin(int value);

		static std::string integerToHex(int value);

		static std::string integerToHexShort(int value);

		static long long readUWord(SeekableDataInput *f);

		static int readUByte(SeekableDataInput *f);

		static int readUHalf(SeekableDataInput *f);

		static int readWord(SeekableDataInput *f);

		static void readBytesToBuffer(SeekableDataInput *f, ByteBuffer *buf, int offset, int size);
		static void copyByteBuffertoByteBuffer(ByteBuffer *src, ByteBuffer *dst, int offset, int size);
		static std::string readStringZ(SeekableDataInput *f);

		static std::string readStringZ(signed char mem[], int offset);

		static std::string readStringZ(ByteBuffer *buf, int offset);
		static std::string readStringZ(ByteBuffer *buf);
		static std::string readStringNZ(ByteBuffer *buf, int offset, int n);
	   static short getUnsignedByte(ByteBuffer *bb);
	   static short readUByte(ByteBuffer *buf);
	   static int readUHalf(ByteBuffer *buf);
		static long long readUWord(ByteBuffer *buf);
		static int readWord(ByteBuffer *buf);
	};

}
