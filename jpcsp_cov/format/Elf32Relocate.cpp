using namespace std;

#include "Elf32Relocate.h"
#include "../util/Utilities.h"

namespace jpcsp::format
{
	using namespace jpcsp::util;
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
//	import static jpcsp.util.Utilities.*;

	int Elf32Relocate::sizeof_Keyword()
	{
		return 8;
	}

	void Elf32Relocate::read(ByteBuffer *f)
	{
		setR_offset(Utilities::readUWord(f));
		setR_info(Utilities::readUWord(f));
	}

	string Elf32Relocate::toString()
	{
		StringBuilder *str = new StringBuilder();
		str->append("r_offset " + "\t " + Utilities::formatString("long", Long::toHexString(getR_offset() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("r_info " + "\t\t " + Utilities::formatString("long", Long::toHexString(getR_info() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");

		delete str;
		return str->toString();
	}

	long long Elf32Relocate::getR_offset()
	{
		return r_offset;
	}

	void Elf32Relocate::setR_offset(long long r_offset)
	{
		this->r_offset = r_offset;
	}

	long long Elf32Relocate::getR_info()
	{
		return r_info;
	}

	void Elf32Relocate::setR_info(long long r_info)
	{
		this->r_info = r_info;
	}
}
