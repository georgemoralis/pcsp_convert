using namespace std;

#include "Elf32StubHeader.h"
#include "../util/Utilities.h"

namespace jpcsp::format
{
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using Memory = jpcsp::Memory;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;

	int Elf32StubHeader::sizeof_Keyword()
	{
		return 20;
	}

	Elf32StubHeader::Elf32StubHeader(ByteBuffer *f)
	{
		s_modulenamez = "";

		s_modulename = Utilities::readUWord(f);
		s_version = Utilities::readUHalf(f);
		s_flags = Utilities::readUHalf(f);
		s_size = Utilities::readUHalf(f);
		s_imports = Utilities::readUHalf(f);
		s_nid = Utilities::readUWord(f);
		s_text = Utilities::readUWord(f);
	}

	Elf32StubHeader::Elf32StubHeader(Memory *mem, int address)
	{
		s_modulenamez = "";

		s_modulename = mem->read32(address);
		s_version = mem->read16(address + 4);
		s_flags = mem->read16(address + 6);
		s_size = mem->read16(address + 8);
		s_imports = mem->read16(address + 10);
		s_nid = mem->read32(address + 12);
		s_text = mem->read32(address + 16);
	}

	string Elf32StubHeader::toString()
	{
		StringBuilder *str = new StringBuilder();
		if (s_modulenamez != "" && s_modulenamez.length() > 0)
		{
			str->append(s_modulenamez + "\n");
		}
		str->append("s_modulename" + "\t" + Utilities::formatString("long", Long::toHexString(s_modulename & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("s_version" + "\t\t" + Utilities::formatString("short", Long::toHexString(s_version & 0xFFFF)->toUpperCase()) + "\n");
		str->append("s_flags" + "\t\t\t" + Utilities::formatString("short", Long::toHexString(s_flags & 0xFFFF)->toUpperCase()) + "\n");
		str->append("s_size" + "\t\t\t" + Utilities::formatString("short", Long::toHexString(s_size & 0xFFFF)->toUpperCase()) + "\n");
		str->append("s_imports" + "\t\t" + Utilities::formatString("short", Long::toHexString(s_imports & 0xFFFF)->toUpperCase()) + "\n");
		str->append("s_nid" + "\t\t\t" + Utilities::formatString("long", Long::toHexString(s_nid & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("s_text" + "\t\t\t" + Utilities::formatString("long", Long::toHexString(s_text & 0xFFFFFFFFLL)->toUpperCase()) + "\n");

		delete str;
		return str->toString();
	}

	string Elf32StubHeader::getModuleNamez()
	{
		return s_modulenamez;
	}

	void Elf32StubHeader::setModuleNamez(const string &moduleName)
	{
		s_modulenamez = moduleName;
	}

	long long Elf32StubHeader::getOffsetModuleName()
	{
		return s_modulename;
	}

	int Elf32StubHeader::getVersion()
	{
		return s_version;
	}

	int Elf32StubHeader::getFlags()
	{
		return s_flags;
	}

	int Elf32StubHeader::getSize()
	{
		return s_size;
	}

	int Elf32StubHeader::getImports()
	{
		return s_imports;
	}

	long long Elf32StubHeader::getOffsetNid()
	{
		return s_nid;
	}

	long long Elf32StubHeader::getOffsetText()
	{
		return s_text;
	}
}
