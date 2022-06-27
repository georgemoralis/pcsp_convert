using namespace std;

#include "SceIoStat.h"

namespace jpcsp::HLE
{
	using Memory = jpcsp::Memory;

	SceIoStat::SceIoStat(int mode, int attr, long long size, ScePspDateTime *ctime, ScePspDateTime *atime, ScePspDateTime *mtime)
	{
		this->mode = mode;
		this->attr = attr;
		this->size = size;
		this->ctime = ctime;
		this->atime = atime;
		this->mtime = mtime;
	}

	void SceIoStat::write(Memory *mem, int address)
	{
		mem->write32(address, mode);
		mem->write32(address + 4, attr);
		mem->write64(address + 8, size);

		ctime->write(mem, address + 16);
		atime->write(mem, address + 32);
		mtime->write(mem, address + 48);

		// 6 ints reserved
		mem->write32(address + 64, 0xcdcdcdcd);
		mem->write32(address + 68, 0xcdcdcdcd);
		mem->write32(address + 72, 0xcdcdcdcd);
		mem->write32(address + 76, 0xcdcdcdcd);
		mem->write32(address + 80, 0xcdcdcdcd);
		mem->write32(address + 84, 0xcdcdcdcd);
	}

	int SceIoStat::sizeof_Keyword()
	{
		return 16 + ScePspDateTime::sizeof_Keyword() * 3 + 24;
	}
}
