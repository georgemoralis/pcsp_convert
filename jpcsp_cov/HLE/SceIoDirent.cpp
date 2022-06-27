using namespace std;

#include "SceIoDirent.h"

namespace jpcsp::HLE
{
	using Memory = jpcsp::Memory;

	SceIoDirent::SceIoDirent(SceIoStat *stat, const string &filename)
	{
		this->stat = stat;
		this->filename = filename;
	}

	void SceIoDirent::write(Memory *mem, int address)
	{
		int len, i;

		stat->write(mem, address);

		len = filename.length();
		if (len > 256)
		{
			len = 256;
		}

		for (i = 0; i < len; i++)
		{
			mem->write8(address + SceIoStat::sizeof_Keyword() + i, static_cast<signed char>(filename[i]));
		}

		// Zero out remaining space, we need at least 1 to safely terminate the string
		for (; i < 256; i++)
		{
			mem->write8(address + SceIoStat::sizeof_Keyword() + i, static_cast<signed char>(0));
		}

		// 2 ints reserved
		mem->write32(address + SceIoStat::sizeof_Keyword() + 256, 0xcdcdcdcd);
		mem->write32(address + SceIoStat::sizeof_Keyword() + 256 + 4, 0xcdcdcdcd);
	}

	int SceIoDirent::sizeof_Keyword()
	{
		return SceIoStat::sizeof_Keyword() + 256 + 8;
	}
}
