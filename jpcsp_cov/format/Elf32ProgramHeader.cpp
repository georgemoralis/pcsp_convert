using namespace std;

#include "Elf32ProgramHeader.h"

namespace jpcsp::format
{
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using namespace jpcsp::filesystems;
	using Utilities = jpcsp::util::Utilities;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;

	int Elf32ProgramHeader::sizeof_Keyword()
	{
		return 32;
	}

	Elf32ProgramHeader::Elf32ProgramHeader(ByteBuffer *f)
	{
		read(f);
	}

	void Elf32ProgramHeader::read(ByteBuffer *f)
	{
		p_type = Utilities::readUWord(f);
		p_offset = Utilities::readUWord(f);
		p_vaddr = Utilities::readUWord(f);
		p_paddr = Utilities::readUWord(f);
		p_filesz = Utilities::readUWord(f);
		p_memsz = Utilities::readUWord(f);
		p_flags = Utilities::readUWord(f);
		p_align = Utilities::readUWord(f);
	}

	string Elf32ProgramHeader::toString()
	{
		StringBuilder *str = new StringBuilder();
		str->append("p_type " + "\t\t " + Utilities::formatString("long", Long::toHexString(getP_type() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_offset " + "\t " + Utilities::formatString("long", Long::toHexString(getP_offset() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_vaddr " + "\t " + Utilities::formatString("long", Long::toHexString(getP_vaddr() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_paddr " + "\t " + Utilities::formatString("long", Long::toHexString(getP_paddr() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_filesz " + "\t " + Utilities::formatString("long", Long::toHexString(getP_filesz() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_memsz " + "\t " + Utilities::formatString("long", Long::toHexString(getP_memsz() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_flags " + "\t " + Utilities::formatString("long", Long::toHexString(getP_flags() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_align " + "\t " + Utilities::formatString("long", Long::toHexString(getP_align() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");

		delete str;
		return str->toString();
	}

	long long Elf32ProgramHeader::getP_type()
	{
		return p_type;
	}

	long long Elf32ProgramHeader::getP_offset()
	{
		return p_offset;
	}

	long long Elf32ProgramHeader::getP_vaddr()
	{
		return p_vaddr;
	}

	long long Elf32ProgramHeader::getP_paddr()
	{
		return p_paddr;
	}

	long long Elf32ProgramHeader::getP_filesz()
	{
		return p_filesz;
	}

	long long Elf32ProgramHeader::getP_memsz()
	{
		return p_memsz;
	}

	long long Elf32ProgramHeader::getP_flags()
	{
		return p_flags;
	}

	long long Elf32ProgramHeader::getP_align()
	{
		return p_align;
	}
}
