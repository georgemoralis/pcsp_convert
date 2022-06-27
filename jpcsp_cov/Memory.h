#pragma once

#include "HLE/pspdisplay.h"
#include "MemoryMap.h"
#include <iostream>
#include <stdexcept>

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
namespace jpcsp
{

	using ByteBuffer = java::nio::ByteBuffer;
	using namespace jpcsp;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.MemoryMap.*;

	class Memory
	{
	private:
		static constexpr int PAGE_COUNT = 0x00100000;
		static constexpr int PAGE_MASK = 0x00000FFF;
		static constexpr int PAGE_SHIFT = 12;

		static constexpr int INDEX_SCRATCHPAD = 0;
		static const int INDEX_VRAM = static_cast<int>(static_cast<unsigned int>(MemoryMap::SIZE_SCRATCHPAD) >> PAGE_SHIFT);
		static const int INDEX_RAM = INDEX_VRAM + (static_cast<int>(static_cast<unsigned int>(MemoryMap::SIZE_VRAM) >> PAGE_SHIFT));

		static const int SIZE_ALLMEM = MemoryMap::SIZE_SCRATCHPAD + MemoryMap::SIZE_VRAM + MemoryMap::SIZE_RAM;

		static Memory *instance;

		signed char *all; // all psp memory is held in here
		static int *map; // hold map of memory
		ByteBuffer *buf; // for easier memory reads/writes

	public:
		ByteBuffer *scratchpad;
		ByteBuffer *videoram;
		ByteBuffer *mainmemory;

		virtual ~Memory()
		{
			delete[] all;
			delete buf;
			delete scratchpad;
			delete videoram;
			delete mainmemory;
		}

		static Memory *get_instance();

		virtual void NullMemory();

	private:
		Memory();

		void buildMap();


	public:
		static int indexFromAddr(int address);

		virtual bool isAddressGood(int address);

		virtual int read8(int address);

		virtual int read16(int address);

		virtual int read32(int address);

		virtual int read32(int page, int address);

		virtual void write8(int address, signed char data);

		virtual void write8(int page, int address, signed char data);

		virtual void write16(int address, short data);

		virtual void write32(int address, int data);

		virtual void write32(int page, int address, int data);

		virtual void write64(int address, long long data);
	};

}
