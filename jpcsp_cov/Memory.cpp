using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "Memory.h"
#include "Emulator.h"

namespace jpcsp
{
	using ByteBuffer = java::nio::ByteBuffer;
	using ByteOrder = java::nio::ByteOrder;
	using pspdisplay = jpcsp::HLE::pspdisplay;
	using namespace jpcsp;
//	import static jpcsp.MemoryMap.*;
Memory *Memory::instance = nullptr;
int *Memory::map;

	Memory *Memory::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new Memory();
		}
		return instance;
	}

	void Memory::NullMemory()
	{
		instance = nullptr;
	}

	Memory::Memory()
	{
		all = new signed char[SIZE_ALLMEM];
		map = new int[PAGE_COUNT];
		buf = ByteBuffer::wrap(all);
		buf->order(ByteOrder::LITTLE_ENDIAN);

		scratchpad = ByteBuffer::wrap(all, 0, MemoryMap::SIZE_SCRATCHPAD).slice();
		scratchpad->order(ByteOrder::LITTLE_ENDIAN);

		videoram = ByteBuffer::wrap(all, MemoryMap::SIZE_SCRATCHPAD, MemoryMap::SIZE_VRAM).slice();
		videoram->order(ByteOrder::LITTLE_ENDIAN);

		mainmemory = ByteBuffer::wrap(all, MemoryMap::SIZE_SCRATCHPAD + MemoryMap::SIZE_VRAM, MemoryMap::SIZE_RAM).slice();
		mainmemory->order(ByteOrder::LITTLE_ENDIAN);

		buildMap();
	}

	void Memory::buildMap()
	{
		int i;
		int page;

		for (i = 0; i < PAGE_COUNT; ++i)
		{
			map[i] = -1;
		}

		page = static_cast<int>(static_cast<unsigned int>(MemoryMap::START_SCRATCHPAD) >> PAGE_SHIFT);
		for (i = 0; i < (static_cast<int>(static_cast<unsigned int>(MemoryMap::SIZE_SCRATCHPAD) >> PAGE_SHIFT)); ++i)
		{
			map[0x00000 + page + i] = (INDEX_SCRATCHPAD + i) << PAGE_SHIFT;
			map[0x40000 + page + i] = (INDEX_SCRATCHPAD + i) << PAGE_SHIFT;
			map[0x80000 + page + i] = (INDEX_SCRATCHPAD + i) << PAGE_SHIFT;
		}

		page = static_cast<int>(static_cast<unsigned int>(MemoryMap::START_VRAM) >> PAGE_SHIFT);
		for (i = 0; i < (static_cast<int>(static_cast<unsigned int>(MemoryMap::SIZE_VRAM) >> PAGE_SHIFT)); ++i)
		{
			map[0x00000 + page + i] = (INDEX_VRAM + i) << PAGE_SHIFT;
			map[0x40000 + page + i] = (INDEX_VRAM + i) << PAGE_SHIFT;
			map[0x80000 + page + i] = (INDEX_VRAM + i) << PAGE_SHIFT;
		}

		page = static_cast<int>(static_cast<unsigned int>(MemoryMap::START_RAM) >> PAGE_SHIFT);
		for (i = 0; i < (static_cast<int>(static_cast<unsigned int>(MemoryMap::SIZE_RAM) >> PAGE_SHIFT)); ++i)
		{
			map[0x00000 + page + i] = (INDEX_RAM + i) << PAGE_SHIFT;
			map[0x40000 + page + i] = (INDEX_RAM + i) << PAGE_SHIFT;
			map[0x80000 + page + i] = (INDEX_RAM + i) << PAGE_SHIFT;
		}
	}

	int Memory::indexFromAddr(int address)
	{
		int index = map[static_cast<int>(static_cast<unsigned int>(address) >> PAGE_SHIFT)];
		if (index == -1)
		{
			throw runtime_error("Invalid memory address : " + Integer::toHexString(address) + " PC=" + Integer::toHexString(Emulator::getProcessor()->pc));
		}
		return index;
	}

	bool Memory::isAddressGood(int address)
	{
		int index = map[static_cast<int>(static_cast<unsigned int>(address) >> PAGE_SHIFT)];
		return (index != -1);
	}

	int Memory::read8(int address)
	{
		try
		{
			int page = indexFromAddr(address);
			return static_cast<int>(buf->get(page + (address & PAGE_MASK))) & 0xFF;
		}
		catch (const runtime_error &e)
		{
			cout << "read8 - " << e.what() << endl;
			Emulator::PauseEmu();
			return 0;
		}
	}

	int Memory::read16(int address)
	{
		try
		{
			int page = indexFromAddr(address);
			return static_cast<int>(buf->getShort(page + (address & PAGE_MASK))) & 0xFFFF;
		}
		catch (const runtime_error &e)
		{
			cout << "read16 - " << e.what() << endl;
			Emulator::PauseEmu();
			return 0;
		}
	}

	int Memory::read32(int address)
	{
		try
		{
			int page = indexFromAddr(address);
			return buf->getInt(page + (address & PAGE_MASK));
		}
		catch (const runtime_error &e)
		{
			cout << "read32 - " << e.what() << endl;
			Emulator::PauseEmu();
			return 0;
		}
	}

	int Memory::read32(int page, int address)
	{
		try
		{
			return buf->getInt(page + (address & PAGE_MASK));
		}
		catch (const runtime_error &e)
		{
			cout << "read32 - " << e.what() << endl;
			Emulator::PauseEmu();
			return 0;
		}
	}

	void Memory::write8(int address, signed char data)
	{
		try
		{
			int page = indexFromAddr(address);
			buf->put(page + (address & PAGE_MASK), data);
			pspdisplay::get_instance()->write8(address, data);
		}
		catch (const runtime_error &e)
		{
			cout << "write8 - " << e.what() << endl;
			Emulator::PauseEmu();
		}
	}

	void Memory::write8(int page, int address, signed char data)
	{
		try
		{
			buf->put(page + (address & PAGE_MASK), data);
			pspdisplay::get_instance()->write8(address, data);
		}
		catch (const runtime_error &e)
		{
			cout << "write8 - " << e.what() << endl;
			Emulator::PauseEmu();
		}
	}

	void Memory::write16(int address, short data)
	{

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
