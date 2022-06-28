/*
 *  28/06/2022 - synced with jpcsp 16/9/2008 2a9c39b0  Completed!
 */
#pragma once

namespace MemoryMap {  
    const u32 START_SCRATCHPAD = 0x00010000;
    const u32 END_SCRATCHPAD = 0x00013FFF;
    const u32 SIZE_SCRATCHPAD = END_SCRATCHPAD - START_SCRATCHPAD + 1;


    const u32 START_VRAM = 0x04000000;  // KU0
    const u32 END_VRAM = 0x041FFFFF;  // KU0
    const u32 SIZE_VRAM = END_VRAM - START_VRAM + 1;


    const u32 START_RAM = 0x08000000;
    const u32 END_RAM = 0x09FFFFFF;
    const u32 SIZE_RAM = END_RAM - START_RAM + 1;


    const u32 START_IO_0 = 0x1C000000;
    const u32 END_IO_0 = 0x1FBFFFFF;

    const u32 START_IO_1 = 0x1FD00000;
    const u32 END_IO_1 = 0x1FFFFFFF;

    const u32 START_EXCEPTIO_VEC = 0x1FC00000;
    const u32 END_EXCEPTIO_VEC = 0x1FCFFFFF;

    const u32 START_KERNEL = 0x88000000;  // K0
    const u32 END_KERNEL = 0x887FFFFF;  // K0


    const u32 START_USERSPACE = 0x08800000;  // KU0
    const u32 END_USERSPACE = 0x09FFFFFF;  // KU0


    const u32 START_UNCACHED_RAM_VIDEO = 0x44000000;
    const u32 END_UNCACHED_RAM_VIDEO = 0x441FFFFF;

};
