using namespace std;

#include "Elf32.h"

namespace jpcsp::format
{
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using List = java::util::List;

	vector<Elf32SectionHeader*> Elf32::getListSectionHeader()
	{
		return sectionheaders;
	}

	Elf32::Elf32(ByteBuffer *f)
	{
		header = new Elf32Header(f);
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
		ElfInfo = header->toString();
		ProgInfo = "";
		SectInfo = "";
	}

	Elf32Header *Elf32::getHeader()
	{
		return header;
	}

	void Elf32::setHeader(Elf32Header *header)
	{
		this->header = header;
	}

	void Elf32::setListProgramHeader(vector<Elf32ProgramHeader*> &programheaders)
	{
		this->programheaders = programheaders;
	}

	void Elf32::setListSectionHeader(vector<Elf32SectionHeader*> &sectionheaders)
	{
		this->sectionheaders = sectionheaders;
	}

	string Elf32::getElfInfo()
	{
		return ElfInfo;
	}

	void Elf32::setElfInfo(const string &ElfInfo)
	{
		this->ElfInfo = ElfInfo;
	}

	string Elf32::getProgInfo()
	{
		return ProgInfo;
	}

	void Elf32::setProgInfo(const string &ProgInfo)
	{
		this->ProgInfo = ProgInfo;
	}

	string Elf32::getSectInfo()
	{
		return SectInfo;
	}

	void Elf32::setSectInfo(const string &SectInfo)
	{
		this->SectInfo = SectInfo;
	}
}
