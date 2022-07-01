/*
 * 01/07/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#include "..\PCSPCommon.h"
#include "PSP.h"

PSP::PSP() {}

PSP::PSP(std::ifstream &f) { f.read((char *)&data, sizeof(data)); }

PSP::~PSP() {}

bool PSP::isValid() const { return data.e_magic == 0x5053507E; }
