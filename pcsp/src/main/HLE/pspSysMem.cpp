/*
 * 27/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#include "..\PCSPCommon.h"
#include "Managers/SceUidManager.h"
#include "pspSysMem.h"

static std::map<u32, SysMemInfo> blockList;
static u32 heapTop;
static u32 heapBottom;

SysMemInfo::SysMemInfo(u32 partitionid, const std::string &name, u32 type, u32 size, u32 addr)
    : partitionid(partitionid), name(name), type(type), size(size), addr(addr) {
    uid = SceUidManager::getNewUid("SysMem");
    blockList[uid] = *this;
}

#if 0
    public void Initialise(int programStartAddr, int programSize)
    {
        blockList = new HashMap<Integer, SysMemInfo>();

        System.out.println("pspSysMem reserving " + programSize + " bytes at "
                + String.format("%08x", programStartAddr) + " for app");

        heapBottom = programStartAddr + programSize;
        heapTop = MemoryMap.END_RAM;
    }

    // Allocates to 64-byte alignment
    // TODO use the partitionid
    public int malloc(int partitionid, int type, int size, int addr)
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
                allocatedAddress = addr;
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

    // For internal use, example: ThreadMan allocating stack space
    // Also removes the associated SysMemInfo (if found) from blockList
    public void free(int addr)
    {
        boolean found = false;

        // Reverse lookup on blockList, get SysMemInfo and call free
        for (Iterator<SysMemInfo> it = blockList.values().iterator(); it.hasNext();)
        {
            SysMemInfo info = it.next();
            if (info.addr == addr)
            {
                found = true;
                free(info);
                it.remove();
                break;
            }
        }

        if (!found)
        {
            System.out.println("ERROR failed to map addr to SysMemInfo, possibly bad/missing cleanup or double free in HLE");
        }
    }

    public void free(SysMemInfo info)
    {
        // TODO
    }

    public void sceKernelMaxFreeMemSize()
    {
        int maxFree = heapTop - heapBottom;
        System.out.println("sceKernelMaxFreeMemSize " + maxFree
                + " (hex=" + Integer.toHexString(maxFree) + ")");
        Emulator.getProcessor().gpr[2] = maxFree;
    }

    public void sceKernelTotalFreeMemSize()
    {
        int totalFree = heapTop - heapBottom;
        System.out.println("sceKernelTotalFreeMemSize " + totalFree
                + " (hex=" + Integer.toHexString(totalFree) + ")");
        Emulator.getProcessor().gpr[2] = totalFree;
    }

    /**
     * @param partitionid TODO probably user, kernel etc
     * 0 = ?
     * 1 = kernel?
     * 2 = user?
     * @param type If type is PSP_SMEM_Addr, then addr specifies the lowest
     * address allocate the block from.
     */
    public void sceKernelAllocPartitionMemory(int partitionid, int pname, int type, int size, int addr)
    {
        pname &= 0x3fffffff;
        addr &= 0x3fffffff;
        String name = readStringZ(Memory.get_instance().mainmemory, pname - MemoryMap.START_RAM);

        // print debug info
        String typeStr;
        switch(type) {
            case PSP_SMEM_Low: typeStr = "PSP_SMEM_Low"; break;
            case PSP_SMEM_High: typeStr = "PSP_SMEM_High"; break;
            case PSP_SMEM_Addr: typeStr = "PSP_SMEM_Addr"; break;
            case PSP_SMEM_LowAligned: typeStr = "PSP_SMEM_LowAligned"; break;
            case PSP_SMEM_HighAligned: typeStr = "PSP_SMEM_HighAligned"; break;
            default: typeStr = "UNHANDLED " + type; break;
        }
        System.out.println("sceKernelAllocPartitionMemory(partitionid=" + partitionid
                + ",name='" + name + "',type=" + typeStr + ",size=" + size
                + ",addr=0x" + Integer.toHexString(addr) + ")");

        addr = malloc(partitionid, type, size, addr);
        if (addr != 0)
        {
            SysMemInfo info = new SysMemInfo(partitionid, name, type, size, addr);
            Emulator.getProcessor().gpr[2] = info.uid;
        }
        else
        {
            Emulator.getProcessor().gpr[2] = -1;
        }
    }

    public void sceKernelFreePartitionMemory(int uid) throws GeneralJpcspException
    {
        SceUIDMan.get_instance().checkUidPurpose(uid, "SysMem", true);
        SysMemInfo info = blockList.remove(uid);
        if (info == null) {
            System.out.println("sceKernelFreePartitionMemory unknown SceUID=" + Integer.toHexString(uid));
            Emulator.getProcessor().gpr[2] = -1;
        } else {
            free(info);
            System.out.println("UNIMPLEMENT:sceKernelFreePartitionMemory SceUID=" + Integer.toHexString(info.uid) + " name:'" + info.name + "'");
            Emulator.getProcessor().gpr[2] = 0;
        }
    }

    public void sceKernelGetBlockHeadAddr(int uid) throws GeneralJpcspException
    {
        SceUIDMan.get_instance().checkUidPurpose(uid, "SysMem", true);
        SysMemInfo info = blockList.get(uid);
        if (info == null) {
            System.out.println("sceKernelGetBlockHeadAddr unknown SceUID=" + Integer.toHexString(uid));
            Emulator.getProcessor().gpr[2] = -1;
        } else {
            System.out.println("sceKernelGetBlockHeadAddr SceUID=" + Integer.toHexString(info.uid) + " name:'" + info.name + "' headAddr:" + Integer.toHexString(info.addr));
            Emulator.getProcessor().gpr[2] = info.addr;
        }
    }

    public void sceKernelDevkitVersion()
    {
        // Return 1.5 for now
        System.out.println("sceKernelDevkitVersion 0x01050100");
        Emulator.getProcessor().gpr[2] = 0x01050100;
    }
}
#endif
