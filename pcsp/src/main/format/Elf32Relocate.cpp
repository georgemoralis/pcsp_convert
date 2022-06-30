/*
 * 30/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#include "..\PCSPCommon.h"
#include "Elf32Relocate.h"

Elf32Relocate::Elf32Relocate() {}

Elf32Relocate::Elf32Relocate(std::ifstream &f) { f.read((char *)&data, sizeof(data)); }

void Elf32Relocate::read(std::ifstream &f) { f.read((char *)&data, sizeof(data)); }
Elf32Relocate::~Elf32Relocate() {}

const size_t Elf32Relocate::sizeOf() { return 8; }

std::string Elf32Relocate::toString() const {
    std::string str;
    char tmp[128];

    sprintf(tmp, "r_offset 0x%08X\n", data.r_offset);
    str.append(tmp);
    sprintf(tmp, "r_info   0x%08X\n", data.r_info);
    str.append(tmp);

    return str;
}

u32 Elf32Relocate::getOffset() const { return data.r_offset; }

u32 Elf32Relocate::getInfo() const { return data.r_info; }

void Elf32Relocate::setOffset(u32 offset) { data.r_offset = offset; }

void Elf32Relocate::setInfo(u32 info) { data.r_info = info; }
