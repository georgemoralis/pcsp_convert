#pragma once

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

	class MemoryMap
	{
	public:
		static constexpr int START_SCRATCHPAD = 0x00010000;
		static constexpr int END_SCRATCHPAD = 0x00013FFF;
		static const int SIZE_SCRATCHPAD = END_SCRATCHPAD - START_SCRATCHPAD + 1;

		static constexpr int START_VRAM = 0x04000000; // KU0
		static constexpr int END_VRAM = 0x041FFFFF; // KU0
		static const int SIZE_VRAM = END_VRAM - START_VRAM + 1;

		static constexpr int START_RAM = 0x08000000;
		static constexpr int END_RAM = 0x09FFFFFF;
		static const int SIZE_RAM = END_RAM - START_RAM + 1;

		static constexpr int START_IO_0 = 0x1C000000;
		static constexpr int END_IO_0 = 0x1FBFFFFF;

		static constexpr int START_IO_1 = 0x1FD00000;
		static constexpr int END_IO_1 = 0x1FFFFFFF;

		static constexpr int START_EXCEPTIO_VEC = 0x1FC00000;
		static constexpr int END_EXCEPTIO_VEC = 0x1FCFFFFF;

		static constexpr int START_KERNEL = 0x88000000; // K0
		static constexpr int END_KERNEL = 0x887FFFFF; // K0

		static constexpr int START_USERSPACE = 0x08800000; // KU0
		static constexpr int END_USERSPACE = 0x09FFFFFF; // KU0

		static constexpr int START_UNCACHED_RAM_VIDEO = 0x44000000;
		static constexpr int END_UNCACHED_RAM_VIDEO = 0x441FFFFF;
	};

}
