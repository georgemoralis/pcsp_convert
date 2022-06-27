#pragma once

#include "Elf32Header.h"
#include "Elf32ProgramHeader.h"
#include "Elf32SectionHeader.h"
#include <string>
#include <vector>

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
namespace jpcsp::format
{

	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using List = java::util::List;

	class Elf32
	{

	private:
		Elf32Header *header;
		std::string ElfInfo; // ELF header
		std::string ProgInfo; // ELF program headers
		std::string SectInfo; // ELF section headers
		std::vector<Elf32ProgramHeader*> programheaders;
		std::vector<Elf32SectionHeader*> sectionheaders;

	public:
		virtual ~Elf32()
		{
			delete header;
		}

		virtual std::vector<Elf32SectionHeader*> getListSectionHeader();

		Elf32(ByteBuffer *f);

		virtual Elf32Header *getHeader();

		virtual void setHeader(Elf32Header *header);

		virtual void setListProgramHeader(std::vector<Elf32ProgramHeader*> &programheaders);

		virtual void setListSectionHeader(std::vector<Elf32SectionHeader*> &sectionheaders);

		virtual std::string getElfInfo();

		virtual void setElfInfo(const std::string &ElfInfo);

		virtual std::string getProgInfo();

		virtual void setProgInfo(const std::string &ProgInfo);

		virtual std::string getSectInfo();

		virtual void setSectInfo(const std::string &SectInfo);
	};

}
