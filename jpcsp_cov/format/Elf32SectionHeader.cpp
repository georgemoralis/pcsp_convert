using namespace std;

#include "Elf32SectionHeader.h"
#include "../util/Utilities.h"

namespace jpcsp::format
{
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using Memory = jpcsp::Memory;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;

	int Elf32SectionHeader::sizeof_Keyword()
	{
		return 40;
	}

	Elf32SectionHeader::Elf32SectionHeader(ByteBuffer *f)
	{
		sh_name = Utilities::readUWord(f);
		sh_type = Utilities::readWord(f);
		sh_flags = Utilities::readWord(f);
		sh_addr = Utilities::readUWord(f);
		sh_offset = Utilities::readUWord(f);
		sh_size = Utilities::readUWord(f);
		sh_link = Utilities::readWord(f);
		sh_info = Utilities::readWord(f);
		sh_addralign = Utilities::readWord(f);
		sh_entsize = Utilities::readWord(f);
	}

	Elf32SectionHeader::Elf32SectionHeader(Memory *mem, int address)
	{
		sh_name = mem->read32(address);
		sh_type = mem->read32(address + 4);
		sh_flags = mem->read32(address + 8);
		sh_addr = mem->read32(address + 12);
		sh_offset = mem->read32(address + 16);
		sh_size = mem->read32(address + 20);
		sh_link = mem->read32(address + 24);
		sh_info = mem->read32(address + 28);
		sh_addralign = mem->read32(address + 32);
		sh_entsize = mem->read32(address + 36);
	}

	string Elf32SectionHeader::toString()
	{
		StringBuilder *str = new StringBuilder();
		str->append("sh_name " + "\t " + Utilities::formatString("long", Long::toHexString(getSh_name() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("sh_type " + "\t " + Utilities::formatString("long", Long::toHexString(getSh_type() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("sh_flags " + "\t " + Utilities::integerToHex(getSh_flags() & 0xFF) + "\n");
		str->append("sh_addr " + "\t " + Utilities::formatString("long", Long::toHexString(getSh_addr() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("sh_offset " + "\t " + Utilities::formatString("long", Long::toHexString(getSh_offset() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("sh_size " + "\t " + Utilities::formatString("long", Long::toHexString(getSh_size() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("sh_link " + "\t " + Utilities::integerToHex(getSh_link() & 0xFF) + "\n");
		str->append("sh_info " + "\t " + Utilities::integerToHex(getSh_info() & 0xFF) + "\n");
		str->append("sh_addralign " + "\t " + Utilities::integerToHex(getSh_addralign() & 0xFF) + "\n");
		str->append("sh_entsize " + "\t " + Utilities::formatString("long", Long::toHexString(getSh_entsize() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");

		delete str;
		return str->toString();
	}

	string Elf32SectionHeader::getSh_namez()
	{
		return sh_namez;
	}

	void Elf32SectionHeader::setSh_namez(const string &sh_namez)
	{
		this->sh_namez = sh_namez;
	}

	long long Elf32SectionHeader::getSh_name()
	{
		return sh_name;
	}

	int Elf32SectionHeader::getSh_type()
	{
		return sh_type;
	}

	int Elf32SectionHeader::getSh_flags()
	{
		return sh_flags;
	}

	long long Elf32SectionHeader::getSh_addr()
	{
		return sh_addr;
	}

	long long Elf32SectionHeader::getSh_offset()
	{
		return sh_offset;
	}

	long long Elf32SectionHeader::getSh_size()
	{
		return sh_size;
	}

	int Elf32SectionHeader::getSh_link()
	{
		return sh_link;
	}

	int Elf32SectionHeader::getSh_info()
	{
		return sh_info;
	}

	int Elf32SectionHeader::getSh_addralign()
	{
		return sh_addralign;
	}

	long long Elf32SectionHeader::getSh_entsize()
	{
		return sh_entsize;
	}
}
