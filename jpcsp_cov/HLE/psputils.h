#pragma once

#include "../Emulator.h"
#include "../Memory.h"
#include "../Processor.h"
#include <unordered_map>
#include <iostream>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace jpcsp::HLE { class SceKernelUtilsMt19937Context; }

/*
TODO
- HLE everything in http://psp.jim.sh/pspsdk-doc/psputils_8h.html


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
	using Random = java::util::Random;


	class psputils
	{
	private:
		static psputils *instance;
		int initialclocks = 0;
		std::unordered_map<int, SceKernelUtilsMt19937Context*> Mt19937List;

	public:
		static psputils *get_instance();

	private:
		psputils();

		/** call this when resetting the emulator */
	public:
		virtual void Initialise();

		/** Get the time in seconds since the epoc (1st Jan 1970).  */
		virtual void sceKernelLibcTime(int time_t_addr);

		/** returns the number of clocks since the "process" started.
		 * Current implemention uses clocks since Initialise was last called, and
		 * we are using clocks = seconds * CLOCKS_PER_SEC, where CLOCKS_PER_SEC
		 * is 1 million (1000000). */
	protected:
		int currentClocks = 0;
	public:
		virtual void sceKernelLibcClock();

		virtual void sceKernelDcacheWritebackAll();

		virtual void sceKernelDcacheWritebackInvalidateAll();

		virtual void sceKernelDcacheWritebackRange(int p_addr, int size);

		virtual void sceKernelDcacheWritebackInvalidateRange(int p_addr, int size);

		virtual void sceKernelDcacheInvalidateRange(int p_addr, int size);

		virtual void sceKernelUtilsMt19937Init(int ctx_addr, int seed);

		virtual void sceKernelUtilsMt19937UInt(int ctx_addr);

	private:
		class SceKernelUtilsMt19937Context
		{
		private:
			psputils *outerInstance;

			Random *r;

		public:
			virtual ~SceKernelUtilsMt19937Context()
			{
				delete r;
				delete outerInstance;
			}

			SceKernelUtilsMt19937Context(psputils *outerInstance, int seed);
		};
	};

}
