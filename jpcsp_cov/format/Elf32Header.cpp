using namespace std;

#include "Elf32Header.h"

namespace jpcsp::format
{
	using IOException = java::io::IOException;
	using MemoryMap = jpcsp::MemoryMap;
	using ByteBuffer = java::nio::ByteBuffer;
	using Utilities = jpcsp::util::Utilities;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;

	void Elf32Header::read(ByteBuffer *f)
	{
		e_magic = Utilities::readUWord(f);
		e_class = Utilities::readUByte(f);
		e_data = Utilities::readUByte(f);
		e_idver = Utilities::readUByte(f);
		f->get(getE_pad()); //can raise EOF exception
		e_type = Utilities::readUHalf(f);
		e_machine = Utilities::readUHalf(f);
		e_version = Utilities::readUWord(f);
		e_entry = Utilities::readUWord(f);
		e_phoff = Utilities::readUWord(f);
		e_shoff = Utilities::readUWord(f);
		e_flags = Utilities::readUWord(f);
		e_ehsize = Utilities::readUHalf(f);
		e_phentsize = Utilities::readUHalf(f);
		e_phnum = Utilities::readUHalf(f);
		e_shentsize = Utilities::readUHalf(f);
		e_shnum = Utilities::readUHalf(f);
		e_shstrndx = Utilities::readUHalf(f);
	}

	Elf32Header::Elf32Header(ByteBuffer *f)
	{
	   read(f);
	}

	bool Elf32Header::isValid()
	{
	   return (Long::toHexString(getE_magic() & 0xFFFFFFFFLL)->toUpperCase().equals("464C457F"));
	}

	bool Elf32Header::isMIPSExecutable()
	{
	   return (Integer::toHexString(getE_machine() & 0xFFFF).equals("8"));
	}

	bool Elf32Header::isPRXDetected()
	{
	   return ((getE_type() & 0xFFFF) == 0xFFA0);
	}

	bool Elf32Header::requiresRelocation()
	{
	   return (isPRXDetected() || (getE_entry() < MemoryMap::START_RAM));
	}

	string Elf32Header::toString()
	{
		StringBuilder *str = new StringBuilder();
		str->append("-----ELF HEADER---------" + "\n");
		str->append("e_magic " + "\t " + Utilities::formatString("long", Long::toHexString(getE_magic() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("e_class " + "\t " + Utilities::integerToHex(getE_class() & 0xFF) + "\n");
		// str.append("e_class " + "\t " +  Utilities.formatString("byte", Integer.toHexString(e_class & 0xFF ).toUpperCase())+ "\n");
		str->append("e_data " + "\t\t " + Utilities::formatString("byte", Integer::toHexString(getE_data() & 0xFF)->toUpperCase()) + "\n");
		str->append("e_idver " + "\t " + Utilities::formatString("byte", Integer::toHexString(getE_idver() & 0xFF)->toUpperCase()) + "\n");
		str->append("e_type " + "\t\t " + Utilities::formatString("short", Integer::toHexString(getE_type() & 0xFFFF)->toUpperCase()) + "\n");
		str->append("e_machine " + "\t " + Utilities::formatString("short", Integer::toHexString(getE_machine() & 0xFFFF)->toUpperCase()) + "\n");
		str->append("e_version " + "\t " + Utilities::formatString("long", Long::toHexString(getE_version() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("e_entry " + "\t " + Utilities::formatString("long", Long::toHexString(getE_entry() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("e_phoff " + "\t " + Utilities::formatString("long", Long::toHexString(getE_phoff() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("e_shoff " + "\t " + Utilities::formatString("long", Long::toHexString(getE_shoff() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("e_flags " + "\t " + Utilities::formatString("long", Long::toHexString(getE_flags() & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("e_ehsize " + "\t " + Utilities::formatString("short", Integer::toHexString(getE_ehsize() & 0xFFFF)->toUpperCase()) + "\n");
		str->append("e_phentsize " + "\t " + Utilities::formatString("short", Integer::toHexString(getE_phentsize() & 0xFFFF)->toUpperCase()) + "\n");
		str->append("e_phnum " + "\t " + Utilities::formatString("short", Integer::toHexString(getE_phnum() & 0xFFFF)->toUpperCase()) + "\n");
		str->append("e_shentsize " + "\t " + Utilities::formatString("short", Integer::toHexString(getE_shentsize() & 0xFFFF)->toUpperCase()) + "\n");
		str->append("e_shnum " + "\t " + Utilities::formatString("short", Integer::toHexString(getE_shnum() & 0xFFFF)->toUpperCase()) + "\n");
		str->append("e_shstrndx " + "\t " + Utilities::formatString("short", Integer::toHexString(getE_shstrndx() & 0xFFFF)->toUpperCase()) + "\n");

		delete str;
		return str->toString();
	}

	long long Elf32Header::getE_magic()
	{
		return e_magic;
	}

	int Elf32Header::getE_class()
	{
		return e_class;
	}

	int Elf32Header::getE_data()
	{
		return e_data;
	}

	int Elf32Header::getE_idver()
	{
		return e_idver;
	}

	signed char *Elf32Header::getE_pad()
	{
		return e_pad;
	}

	int Elf32Header::getE_type()
	{
		return e_type;
	}

	int Elf32Header::getE_machine()
	{
		return e_machine;
	}

	long long Elf32Header::getE_version()
	{
		return e_version;
	}

	long long Elf32Header::getE_entry()
	{
		return e_entry;
	}

	long long Elf32Header::getE_phoff()
	{
		return e_phoff;
	}

	long long Elf32Header::getE_shoff()
	{
		return e_shoff;
	}

	long long Elf32Header::getE_flags()
	{
		return e_flags;
	}

	int Elf32Header::getE_ehsize()
	{
		return e_ehsize;
	}

	int Elf32Header::getE_phentsize()
	{
		return e_phentsize;
	}

	int Elf32Header::getE_phnum()
	{
		return e_phnum;
	}

	int Elf32Header::getE_shentsize()
	{
		return e_shentsize;
	}

	int Elf32Header::getE_shnum()
	{
		return e_shnum;
	}

	int Elf32Header::getE_shstrndx()
	{
		return e_shstrndx;
	}
}
