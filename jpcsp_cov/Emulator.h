#pragma once

#include "Debugger/MemoryViewer.h"
#include "Debugger/DisassemblerModule/DisassemblerFrame.h"
#include "format/DeferredStub.h"
#include "format/Elf32.h"
#include "format/Elf32Relocate.h"
#include "format/Elf32SectionHeader.h"
#include "format/Elf32StubHeader.h"
#include "Processor.h"
#include "Controller.h"
#include "FileManager.h"
#include "MainGUI.h"
#include "filesystems/SeekableDataInput.h"
#include "Memory.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <mutex>
#include "exceptionhelper.h"

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
	using ByteBuffer = java::nio::ByteBuffer;
	using MemoryViewer = jpcsp::Debugger::MemoryViewer;
	using DisassemblerFrame = jpcsp::Debugger::DisassemblerModule::DisassemblerFrame;
	using Elf32 = jpcsp::format::Elf32;
	using namespace jpcsp::util;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;
	using namespace jpcsp::filesystems;

	//import jpcsp.util.Utilities;
	class Emulator : public Runnable
	{
		private:
			std::mutex lock_object;


	public:
		static std::string ElfInfo;
			static std::string ProgInfo;
			static std::string PbpInfo;
			static std::string SectInfo;
	private:
		static Processor *cpu;
		static Controller *controller;
		FileManager *romManager;
		bool mediaImplemented = false;
		Thread *mainThread;
	public:
//JAVA TO C++ CONVERTER NOTE: Field name conflicts with a method name of the current type:
		static bool run_Conflict;
		static bool pause;
	private:
		static MainGUI *gui;
		static DisassemblerFrame *debugger;
		static MemoryViewer *memview;

	public:
		static int *textsection;
		static int *initsection;
		static int *finisection;
		static int *Stubtextsection;

		virtual ~Emulator()
		{
			delete romManager;
			delete mainThread;
		}

		Emulator(MainGUI *gui);

		virtual void load(SeekableDataInput *f);

		virtual void load(ByteBuffer *f);

	private:
		void processLoading(ByteBuffer *f);

		//elf32 initElf32
		void initElf32();

		void initPbp();

		void initRamBy(Elf32 *elf);

		void initCpuBy(Elf32 *elf);

		void initDebugWindowsByPbp();

		void initDebugWindowsByElf32();

		void initNewPsp();

	public:
		void run() override;

		virtual void RunEmu();

		// static so Memory can pause emu on invalid read/write
		static void PauseEmu();

		static void setFpsTitle(const std::string &fps);

		static Processor *getProcessor();

		static Memory *getMemory();

		static Controller *getController();

		virtual void setDebugger(DisassemblerFrame *debugger);

		virtual void setMemoryViewer(MemoryViewer *memview);
	};

}
