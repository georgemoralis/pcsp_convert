/*
 * 01/07/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#pragma once

#include "Elf32Header.h"
#include "Elf32ProgramHeader.h"
#include "Elf32SectionHeader.h"

class Elf32 
{
   public:
    Elf32();
    Elf32(std::ifstream &f);
    ~Elf32();
    Elf32Header &getHeader();
    void Elf32setHeader(Elf32Header &header);
    std::vector<Elf32SectionHeader> &getListSectionHeader();
    void setListProgramHeader(std::vector<Elf32ProgramHeader> programheaders);
    void setListSectionHeader(std::vector<Elf32SectionHeader> sectionheaders);
    void setElfInfo(std::string ElfInfo);
    void setProgInfo(std::string ProgInfo);
    void setSectInfo(std::string SectInfo);
    std::string getElfInfo() const;
    std::string getProgInfo() const;
    std::string getSectInfo() const;
   private:
    Elf32Header header;
    std::vector<Elf32ProgramHeader> programheaders;
    std::vector<Elf32SectionHeader> sectionheaders;

    std::string ElfInfo;   // ELF header
    std::string ProgInfo;  // ELF program headers
    std::string SectInfo;  // ELF section headers
};
