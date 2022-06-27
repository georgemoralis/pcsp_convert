/*
* 27/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
* 
*/
#pragma once

enum PspDisplayPixelFormat {
    PSP_DISPLAY_PIXEL_FORMAT_565 = 0,
    PSP_DISPLAY_PIXEL_FORMAT_5551 = 1,
    PSP_DISPLAY_PIXEL_FORMAT_4444 = 2,
    PSP_DISPLAY_PIXEL_FORMAT_8888 = 3,
};
enum PspDisplaySetBufSync {
    PSP_DISPLAY_SETBUF_IMMEDIATE = 0,
    PSP_DISPLAY_SETBUF_NEXTFRAME = 1,
};

enum PspDisplayErrorCodes {
    PSP_DISPLAY_ERROR_OK = 0,
    PSP_DISPLAY_ERROR_POINTER  = 0x80000103,
    PSP_DISPLAY_ERROR_ARGUMENT = 0x80000107,
};
namespace pspdisplay {
    void write8(u32 address, u8 data);
    void write16(u32 address, u16 data);
    void write32(u32 address, u32 data);
    void setDirty(bool dirty);
};
