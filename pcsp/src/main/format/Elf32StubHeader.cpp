/*
 * 30/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#include "..\PCSPCommon.h"
#include "..\Memory.h"
#include "Elf32StubHeader.h"

Elf32StubHeader::Elf32StubHeader() {}

Elf32StubHeader::Elf32StubHeader(std::ifstream &f) {
    s_modulenamez.clear();
    f.read((char *)&data, sizeof(data));
}

Elf32StubHeader::Elf32StubHeader(u32 address) {
    s_modulenamez.clear();
    memcpy(&data, Memory::getPointer(address), sizeof(data));
}
Elf32StubHeader::~Elf32StubHeader() {}

const size_t Elf32StubHeader::sizeOf() { return 20; }

std::string Elf32StubHeader::toString() const {
    std::string str;
    char tmp[128];

    if (s_modulenamez.length() > 0) {
        str.append(s_modulenamez);
        str.append("\n");
    }

    sprintf(tmp, "s_modulename 0x%08X\n", data.s_modulename);
    str.append(tmp);
    sprintf(tmp, "s_version    0x%04X\n", data.s_version);
    str.append(tmp);
    sprintf(tmp, "s_flags      0x%04X\n", data.s_flags);
    str.append(tmp);
    sprintf(tmp, "s_size       0x%04X\n", data.s_size);
    str.append(tmp);
    sprintf(tmp, "s_imports    0x%04X\n", data.s_imports);
    str.append(tmp);
    sprintf(tmp, "s_nid        0x%08X\n", data.s_nid);
    str.append(tmp);
    sprintf(tmp, "s_text       0x%08X\n", data.s_text);
    str.append(tmp);

    return str;
}

std::string Elf32StubHeader::getModuleNamez() const { return s_modulenamez; }

void Elf32StubHeader::setModuleNamez(const std::string &moduleName) { s_modulenamez = moduleName; }

u32 Elf32StubHeader::getOffsetModuleName() const { return data.s_modulename; }

u16 Elf32StubHeader::getVersion() const { return data.s_version; }

u16 Elf32StubHeader::getFlags() const { return data.s_flags; }

u16 Elf32StubHeader::getSize() const { return data.s_size; }

u16 Elf32StubHeader::getImports() const { return data.s_imports; }

u32 Elf32StubHeader::getOffsetNid() const { return data.s_nid; }

u32 Elf32StubHeader::getOffsetText() const { return data.s_text; }
