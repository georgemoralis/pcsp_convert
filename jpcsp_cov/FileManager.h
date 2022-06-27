#pragma once

#include "format/DeferredStub.h"
#include "format/Elf32.h"
#include "format/Elf32Header.h"
#include "format/Elf32ProgramHeader.h"
#include "format/Elf32SectionHeader.h"
#include "format/PBP.h"
#include "format/PSP.h"
#include "format/PSPModuleInfo.h"
#include "util/Utilities.h"
#include "filesystems/SeekableDataInput.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <regex>
#include "exceptionhelper.h"
#include "stringbuilder.h"

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

	using IOException = java::io::IOException;
	using namespace jpcsp::filesystems;
	using ByteBuffer = java::nio::ByteBuffer;
	using List = java::util::List;
	using DeferredStub = jpcsp::format::DeferredStub;
	using Elf32 = jpcsp::format::Elf32;
	using Elf32Header = jpcsp::format::Elf32Header;
	using Elf32SectionHeader = jpcsp::format::Elf32SectionHeader;
	using PBP = jpcsp::format::PBP;
	using PSP = jpcsp::format::PSP;
	using PSPModuleInfo = jpcsp::format::PSPModuleInfo;

	class FileManager
	{
	public:
		static std::string ElfInfo; // TODO : think a better way
			static std::string ProgInfo;
			static std::string PbpInfo;
			static std::string SectInfo;

	private:
		PSPModuleInfo *moduleInfo;
		PBP *pbp;
		Elf32 *elf;
		PSP *psp;
		ByteBuffer *actualFile;
		std::string filePath;
	public:
		static constexpr int FORMAT_ELF = 0;
		static constexpr int FORMAT_PBP = 10;
		static constexpr int FORMAT_UMD = 20;
		static constexpr int FORMAT_ISO = 30;
		static constexpr int FORMAT_PSP = 40;
	private:
		int type = -1;
		long long elfoffset = 0;
		long long baseoffset = 0;
		int loadAddressLow = 0, loadAddressHigh = 0; // The space consumed by the program image
		std::vector<DeferredStub*> deferredImports;
		SeekableDataInput *iso;
	public:
		virtual ~FileManager()
		{
			delete moduleInfo;
			delete pbp;
			delete elf;
			delete psp;
			delete actualFile;
			delete iso;
		}

		FileManager(ByteBuffer *f);
		FileManager(SeekableDataInput *iso);
		virtual PSPModuleInfo *getPSPModuleInfo();

		virtual PBP *getPBP();

		virtual Elf32 *getElf32();

		virtual ByteBuffer *getActualFile();

	private:
		void setActualFile(ByteBuffer *f);

		void loadAndDefine(ByteBuffer *f);

	public:
		virtual int getType();

	private:
		void processElf();

		void readElf32Header();

		void processPbp();

		void readElfProgramHeaders();

		void readElfSectionHeaders();

		Elf32SectionHeader *firstStep(Elf32Header *ehdr, ByteBuffer *f, std::vector<Elf32SectionHeader*> &sectionheaders);

		void secondStep(std::vector<Elf32SectionHeader*> &sectionheaders, Elf32SectionHeader *shstrtab, ByteBuffer *f, PSPModuleInfo *moduleinfo);

	public:
		virtual long long getBaseoffset();

		virtual long long getElfoffset();

		virtual int getLoadAddressLow();

		virtual int getLoadAddressHigh();

		// TODO process deferred imports each time a new module is loaded
		virtual void addDeferredImports(std::vector<DeferredStub*> &list);
	};

}
