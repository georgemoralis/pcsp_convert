#pragma once

#include "../Emulator.h"
#include "../GeneralJpcspException.h"
#include "../Memory.h"
#include "../MemoryMap.h"
#include <string>
#include <unordered_map>
#include <iostream>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace jpcsp::HLE { class SysMemInfo; }

/*
Function:
- http://psp.jim.sh/pspsdk-doc/group__SysMem.html

Notes:
Current allocation scheme doesn't handle partitions, freeing blocks or the
space consumed by the program image.

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

	using HashMap = java::util::HashMap;
	using GeneralJpcspException = jpcsp::GeneralJpcspException;
	using namespace jpcsp::util;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;
	/**
	 *
	 * @author shadow
	 */
	class pspSysMem
	{
	private:
		static pspSysMem *instance;

		static std::unordered_map<int, SysMemInfo*> blockList;
		int heapTop = 0, heapBottom = 0;

		// PspSysMemBlockTypes
	public:
		static constexpr int PSP_SMEM_Low = 0;
		static constexpr int PSP_SMEM_High = 1;
		static constexpr int PSP_SMEM_Addr = 2;
		static constexpr int PSP_SMEM_LowAligned = 3;
		static constexpr int PSP_SMEM_HighAligned = 4;

	private:
		pspSysMem();

	public:
		static pspSysMem *get_instance();

		virtual void Initialise(int programStartAddr, int programSize);

		// Allocates to 64-byte alignment
		// TODO use the partitionid
		virtual int malloc(int partitionid, int type, int size, int addr);

		// For internal use, example: ThreadMan allocating stack space
		// Also removes the associated SysMemInfo (if found) from blockList
		virtual void free(int addr);

		virtual void free(SysMemInfo *info);

		virtual void sceKernelMaxFreeMemSize();

		virtual void sceKernelTotalFreeMemSize();

		/**
		 * @param partitionid TODO probably user, kernel etc
		 * 0 = ?
		 * 1 = kernel?
		 * 2 = user?
		 * @param type If type is PSP_SMEM_Addr, then addr specifies the lowest
		 * address allocate the block from.
		 */
		virtual void sceKernelAllocPartitionMemory(int partitionid, int pname, int type, int size, int addr);

		virtual void sceKernelFreePartitionMemory(int uid);

		virtual void sceKernelGetBlockHeadAddr(int uid);

		virtual void sceKernelDevkitVersion();

	public:
		class SysMemInfo
		{
		private:
			pspSysMem *outerInstance;

		public:
			const int uid;
			const int partitionid;
			const std::string name;
			const int type;
			const int size;
			const int addr;

			virtual ~SysMemInfo()
			{
				delete outerInstance;
			}

			SysMemInfo(pspSysMem *outerInstance, int partitionid, const std::string &name, int type, int size, int addr);

		};
	};

}
