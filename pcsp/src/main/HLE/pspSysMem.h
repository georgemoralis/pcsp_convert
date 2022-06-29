/*
 * 28/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#pragma once

enum pspSysMemBlockType {
    PSP_SMEM_Low = 0,
    PSP_SMEM_High = 1,
    PSP_SMEM_Addr = 2,
    PSP_SMEM_LowAligned = 3,
    PSP_SMEM_HighAligned = 4
};

class SysMemInfo {
   public:
    SysMemInfo() {}
    SysMemInfo(u32 partitionid, const std::string &name, u32 type, u32 size, u32 addr);

    u32 uid;
    u32 partitionid;
    std::string name;
    u32 type;
    u32 size;
    u32 addr;
};

namespace pspSysMem {
    void Initialise(u32 programStartAddr, u32 programSize);
    u32 malloc(u32 partitionid, u32 type, u32 size, u32 addr);
    void free(u32 addr);
    void free(const SysMemInfo &info);
    void sceKernelMaxFreeMemSize();;
    void sceKernelTotalFreeMemSize();
};
