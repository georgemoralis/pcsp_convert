using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "Emulator.h"
#include "NIDMapper.h"
#include "MemoryMap.h"
#include "util/Utilities.h"
#include "AllegrexOpcodes.h"
#include "HLE/pspSysMem.h"
#include "HLE/ThreadMan.h"
#include "HLE/psputils.h"
#include "HLE/pspge.h"
#include "HLE/pspdisplay.h"

namespace jpcsp
{
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using List = java::util::List;
	using LinkedList = java::util::LinkedList;
	using MemoryViewer = jpcsp::Debugger::MemoryViewer;
	using DisassemblerFrame = jpcsp::Debugger::DisassemblerModule::DisassemblerFrame;
	using DeferredStub = jpcsp::format::DeferredStub;
	using Elf32 = jpcsp::format::Elf32;
	using Elf32Relocate = jpcsp::format::Elf32Relocate;
	using Elf32SectionHeader = jpcsp::format::Elf32SectionHeader;
	using ShType = jpcsp::format::Elf32SectionHeader::ShType;
	using Elf32StubHeader = jpcsp::format::Elf32StubHeader;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;
	using namespace jpcsp::filesystems;
string Emulator::ElfInfo;
string Emulator::ProgInfo;
string Emulator::PbpInfo;
string Emulator::SectInfo;
Processor *Emulator::cpu;
Controller *Emulator::controller;
bool Emulator::run = false;
bool Emulator::pause = false;
MainGUI *Emulator::gui;
jpcsp::Debugger::DisassemblerModule::DisassemblerFrame *Emulator::debugger;
jpcsp::Debugger::MemoryViewer *Emulator::memview;
int *Emulator::textsection = new int[2];
int *Emulator::initsection = new int[2];
int *Emulator::finisection = new int[2];
int *Emulator::Stubtextsection = new int[2];

	Emulator::Emulator(MainGUI *gui)
	{
		this->gui = gui;
		cpu = new Processor();

		controller = new Controller();
		mainThread = new Thread(this);
	}

	void Emulator::load(SeekableDataInput *f)
	{
		initNewPsp();
		romManager = new FileManager(f);
		initElf32();

		// Delete breakpoints and reset to PC
		if (debugger != nullptr)
		{
			debugger->resetDebugger();
		}
	}

	void Emulator::load(ByteBuffer *f)
	{
		//  here load fileName, iso or etc...
		processLoading(f);
		if (!mediaImplemented)
		{
			throw IOException("This kind of file format still not supported.");
		}

		// Delete breakpoints and reset to PC
		if (debugger != nullptr)
		{
			debugger->resetDebugger();
		}
	}

	void Emulator::processLoading(ByteBuffer *f)
	{
		initNewPsp();
		romManager = new FileManager(f);

		switch (romManager->getType())
		{
			case FileManager::FORMAT_ELF:
				initElf32(); //RAM, CPU, GPU...
				break;
			case FileManager::FORMAT_ISO:
				break;
			case FileManager::FORMAT_PBP:
				initPbp(); //RAM, CPU, GPU...
				break;
			case FileManager::FORMAT_UMD:
				break;
			case FileManager::FORMAT_PSP:
				break;
			default:
				throw IOException("Is not an acceptable format, please choose the rigth file.");
		}
	}

	void Emulator::initElf32()
	{
		mediaImplemented = true;
		initRamBy(romManager->getElf32());
		initCpuBy(romManager->getElf32());
		initDebugWindowsByElf32();
	}

	void Emulator::initPbp()
	{
		mediaImplemented = true;
		initRamBy(romManager->getPBP()->getElf32());
		initCpuBy(romManager->getPBP()->getElf32());
		initDebugWindowsByPbp();
		//RAM, CPU, GPU...
	}

	void Emulator::initRamBy(Elf32 *elf)
	{
		// Relocation
		if (elf->getHeader()->requiresRelocation())
		{
			for (auto shdr : *elf->getListSectionHeader())
			{
				if (shdr->getSh_type() == Elf32SectionHeader::ShType::PRXREL.getValue()) // 0x00000009
				{
					Elf32Relocate *rel = new Elf32Relocate();
					romManager->getActualFile()->position(static_cast<int>(romManager->getElfoffset() + shdr->getSh_offset()));

					int RelCount = static_cast<int>(shdr->getSh_size()) / Elf32Relocate::sizeof_Keyword();
					cout << shdr->getSh_namez() << ": relocating " << RelCount << " entries" << endl;

					int AHL = 0; // (AHI << 16) | (ALO & 0xFFFF)

					int HI_addr = 0; // We'll use this to relocate R_MIPS_HI16 when we get a R_MIPS_LO16

					// Relocation modes, only 1 is allowed at a time
					bool external = true; // copied from soywiz/pspemulator

					bool local = false;
					bool _gp_disp = false;

					for (int i = 0; i < RelCount; i++)
					{
						rel->read(romManager->getActualFile());

						int R_TYPE = static_cast<int>(rel->getR_info() & 0xFF);
						int OFS_BASE = static_cast<int>((rel->getR_info() >> 8) & 0xFF);
						int ADDR_BASE = static_cast<int>((rel->getR_info() >> 16) & 0xFF);
						//System.out.println("type=" + R_TYPE + ",base=" + OFS_BASE + ",addr=" + ADDR_BASE + "");

						int data = Memory::get_instance()->read32(static_cast<int>(romManager->getBaseoffset()) + static_cast<int>(rel->getR_offset()));
						long long result = 0; // Used to hold the result of relocation, OR this back into data

						// these are the addends?
						// SysV ABI MIPS quote: "Because MIPS uses only Elf32_Rel re-location entries, the relocated field holds the addend."
						int half16 = data & 0x0000FFFF; // 31/07/08 unused (fiveofhearts)

						int word32 = data & 0xFFFFFFFF;
						int targ26 = data & 0x03FFFFFF;
						int hi16 = data & 0x0000FFFF;
						int lo16 = data & 0x0000FFFF;

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
