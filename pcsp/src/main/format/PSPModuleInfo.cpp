/*
 * 30/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#include "..\PCSPCommon.h"
#include "..\Memory.h"
#include "PSPModuleInfo.h"


PSPModuleInfo::PSPModuleInfo() {}

PSPModuleInfo::PSPModuleInfo(std::ifstream &f) { read(f); }


PSPModuleInfo::~PSPModuleInfo() {}

void PSPModuleInfo::read(std::ifstream &f) {
    f.read((char *)&data, sizeof(data));

    // Convert the array of bytes used for the module to C++ std::string.
    // Calculate the length of printable portion of the string, otherwise
    // any extra trailing characters may be printed as garbage.
    size_t len = 0;
    while (len < 28 && data.m_name[len] != 0) ++len;
    m_namez = std::string(data.m_name, 0, len);
}

u16 PSPModuleInfo::getM_attr() const { return data.m_attr; }

u16 PSPModuleInfo::getM_version() const { return data.m_version; }

const char *PSPModuleInfo::getM_name() const { return &data.m_name[0]; }

u32 PSPModuleInfo::getM_gp() const { return data.m_gp; }

u32 PSPModuleInfo::getM_exports() const { return data.m_exports; }

u32 PSPModuleInfo::getM_exp_end() const { return data.m_exp_end; }

u32 PSPModuleInfo::getM_imports() const { return data.m_imports; }

u32 PSPModuleInfo::getM_imp_end() const { return data.m_imp_end; }

std::string PSPModuleInfo::getM_namez() const { return m_namez; }
