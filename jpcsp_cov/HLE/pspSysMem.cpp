using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "pspSysMem.h"
#include "../util/Utilities.h"
#include "SceUIDMan.h"

namespace jpcsp::HLE
{
	using HashMap = java::util::HashMap;
	using Iterator = java::util::Iterator;
	using Emulator = jpcsp::Emulator;
	using GeneralJpcspException = jpcsp::GeneralJpcspException;
	using Memory = jpcsp::Memory;
	using MemoryMap = jpcsp::MemoryMap;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;
pspSysMem *pspSysMem::instance;
unordered_map<int, SysMemInfo*> pspSysMem::blockList;

	pspSysMem::pspSysMem()
	{
	}

	pspSysMem *pspSysMem::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new pspSysMem();
		}
		return instance;
	}

	void pspSysMem::Initialise(int programStartAddr, int programSize)
	{
		blockList = unordered_map<int, SysMemInfo*>();

		cout << "pspSysMem reserving " << programSize << " bytes at " << String::format("%08x", programStartAddr) << " for app" << endl;

		heapBottom = programStartAddr + programSize;
		heapTop = MemoryMap::END_RAM;
	}

	int pspSysMem::malloc(int partitionid, int type, int size, int addr)
	{
		int allocatedAddress = 0;

		// TODO check when we are running out of mem!
		if (type == PSP_SMEM_Low)
		{
			allocatedAddress = heapBottom;
			allocatedAddress = (allocatedAddress + 63) & ~63;
			heapBottom = allocatedAddress + size;
		}
		else if (type == PSP_SMEM_Addr)
		{
			allocatedAddress = heapBottom;
			if (allocatedAddress < addr)
			{
				allocatedAddress = addr;
			}
			allocatedAddress = (allocatedAddress + 63) & ~63;
			heapBottom = allocatedAddress + size;
		}
		else if (type == PSP_SMEM_High)
		{
			allocatedAddress = (heapTop - (size + 63)) & ~63;
			heapTop = allocatedAddress;
		}
		else if (type == PSP_SMEM_LowAligned)
		{
			allocatedAddress = heapBottom;
			allocatedAddress = (allocatedAddress + addr - 1) & ~(addr - 1);
			heapBottom = allocatedAddress + size;
		}
		else if (type == PSP_SMEM_HighAligned)
		{
			allocatedAddress = (heapTop - (size + addr - 1)) & ~(addr - 1);
			heapTop = allocatedAddress;
		}

		return allocatedAddress;
	}

	void pspSysMem::free(int addr)
	{
		bool found = false;

		// Reverse lookup on blockList, get SysMemInfo and call free
		for (Iterator<SysMemInfo*> *it = blockList.values().begin(); it->hasNext();)
		{
			SysMemInfo *info = it->next();
			if (info->addr == addr)
			{
				found = true;
				free(info);
				it->remove();
				break;
			}
		}

		if (!found)
		{
			cout << "ERROR failed to map addr to SysMemInfo, possibly bad/missing cleanup or double free in HLE" << endl;
		}
	}

	void pspSysMem::free(SysMemInfo *info)
	{
		// TODO
	}

	void pspSysMem::sceKernelMaxFreeMemSize()
	{
		int maxFree = heapTop - heapBottom;
		cout << "sceKernelMaxFreeMemSize " << maxFree << " (hex=" << Integer::toHexString(maxFree) << ")" << endl;
		Emulator::getProcessor()->gpr[2] = maxFree;
	}

	void pspSysMem::sceKernelTotalFreeMemSize()
	{
		int totalFree = heapTop - heapBottom;
		cout << "sceKernelTotalFreeMemSize " << totalFree << " (hex=" << Integer::toHexString(totalFree) << ")" << endl;
		Emulator::getProcessor()->gpr[2] = totalFree;
	}

	void pspSysMem::sceKernelAllocPartitionMemory(int partitionid, int pname, int type, int size, int addr)
	{
		pname &= 0x3fffffff;
		addr &= 0x3fffffff;
		string name = Utilities::readStringZ(Memory::get_instance()->mainmemory, pname - MemoryMap::START_RAM);

		// print debug info
		string typeStr;
		switch (type)
		{
			case PSP_SMEM_Low:
				typeStr = "PSP_SMEM_Low";
				break;
			case PSP_SMEM_High:
				typeStr = "PSP_SMEM_High";
				break;
			case PSP_SMEM_Addr:
				typeStr = "PSP_SMEM_Addr";
				break;
			case PSP_SMEM_LowAligned:
				typeStr = "PSP_SMEM_LowAligned";
				break;
			case PSP_SMEM_HighAligned:
				typeStr = "PSP_SMEM_HighAligned";
				break;
			default:
				typeStr = "UNHANDLED " + to_string(type);
				break;
		}
		cout << "sceKernelAllocPartitionMemory(partitionid=" << partitionid << ",name='" << name << "',type=" << typeStr << ",size=" << size << ",addr=0x" << Integer::toHexString(addr) << ")" << endl;

		addr = malloc(partitionid, type, size, addr);
		if (addr != 0)
		{
			SysMemInfo *info = new SysMemInfo(this, partitionid, name, type, size, addr);
			Emulator::getProcessor()->gpr[2] = info->uid;

			delete info;
		}
		else
		{
			Emulator::getProcessor()->gpr[2] = -1;
		}
	}

	void pspSysMem::sceKernelFreePartitionMemory(int uid)
	{
		SceUIDMan::get_instance()->checkUidPurpose(uid, "SysMem", true);
		SysMemInfo *info = blockList.erase(uid);
		if (info == nullptr)
		{
			cout << "sceKernelFreePartitionMemory unknown SceUID=" << Integer::toHexString(uid) << endl;

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
