#pragma once
namespace Emulator 
{
void load(std::ifstream &f);
void processLoading(std::ifstream &f);
void initElf32();
void initPbp();
void initRamBy(Elf32 elf);
};
