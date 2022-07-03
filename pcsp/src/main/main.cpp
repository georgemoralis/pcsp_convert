#include "PCSPCommon.h"
#include "Memory.h"
#include "Video.h"
#include "Cpu.h"
#include "format/Elf32.h"
#include "Emulator.h"

u32 MiniFireCode[] = {
    0x27BDF620, 0x03A02021, 0x00082FCC, 0x3C1108A0, 0x3C1208B0, 0x3C104400, 0x00002021, 0x240501E0, 0x24060110,
    0x00084E8C, 0x02201021, 0x3408B600, 0xA0400000, 0x2508FFFF, 0x0501FFFD, 0x24420001, 0x3634B400, 0x269301FF,
    0x03A02021, 0x0008300C, 0x26940001, 0x0293182B, 0x1460FFFB, 0xA2820000, 0x241501FE, 0x03A02021, 0x0008300C,
    0x24030059, 0x14600002, 0x0043001B, 0x0007000D, 0x00001012, 0x00001810, 0x24630001, 0x00031A40, 0x0071A020,
    0x00551024, 0x24420001, 0x0282A020, 0xA2950000, 0x24080059, 0x3629B200, 0x364BB200, 0x252A01FE, 0x91240200,
    0x91250201, 0x00852021, 0x91250202, 0x00852021, 0x91250001, 0x00852021, 0x00042082, 0x5C800001, 0x2484FFFF,
    0xA1640001, 0x25290001, 0x012A102B, 0x1440FFF2, 0x256B0001, 0x2508FFFF, 0x256BFC02, 0x1D00FFED, 0x2529FC02,
    0x3C080010, 0x02088026, 0x02001021, 0x00004021, 0x02405021, 0x02002021, 0x254B0200, 0x91420000, 0xAC820000,
    0xAC820800, 0xAC821000, 0x254A0001, 0x014B182B, 0x1460FFF9, 0x24840004, 0x25080001, 0x2D02005A, 0x1440FFF4,
    0x24841000, 0x27A409D0, 0x24050001, 0x0008540C, 0x8FA809D4, 0x55000001, 0x00083ACC, 0x000851CC, 0x02002021,
    0x24050200, 0x24060003, 0x24070001, 0x00084FCC, 0x02204021, 0x02408821, 0x0A240024, 0x01009021,
};


int main() {
    if (!Memory::initialize()) return false;
    if (!Video.Initialize()) return false;

    Cpu.Initialize();

    std::string file = "minifire.pbp";
    std::ifstream ifs;
    ifs.open(file.c_str(), std::ios::in | std::ios::binary); 
    std::string filepath = std::filesystem::absolute(std::filesystem::path(&file[0])).parent_path().generic_string();

    if (!ifs.fail()) {
        Emulator::load(ifs);
    }
    

    //for (int i = 0; i < sizeof(MiniFireCode) / 4; ++i) Memory::write32(i * 4 + 0x08900050, MiniFireCode[i]);

    for (;;) {
        Cpu.Step();
    }
}
