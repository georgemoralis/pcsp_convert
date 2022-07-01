/*
 * 01/07/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#include "..\PCSPCommon.h"
#include "Elf32.h"


Elf32::Elf32() {}

Elf32::Elf32(std::ifstream &f) {
    header = Elf32Header(f);
    ElfInfo = header.toString();
    ProgInfo = "";
    SectInfo = "";
}
Elf32::~Elf32() {}


std::vector<Elf32SectionHeader> &Elf32::getListSectionHeader() { return sectionheaders; }

Elf32Header &Elf32::getHeader() { return header; }

void Elf32::Elf32setHeader(Elf32Header &header) { this->header = header; }

void Elf32::setListProgramHeader(std::vector<Elf32ProgramHeader> programheaders) {
    this->programheaders = programheaders;
}

void Elf32::setListSectionHeader(std::vector<Elf32SectionHeader> sectionheaders) {
    this->sectionheaders = sectionheaders;
}

std::string Elf32::getElfInfo() const { return ElfInfo; }

void Elf32::setElfInfo(std::string ElfInfo) { this->ElfInfo = ElfInfo; }

std::string Elf32::getProgInfo() const { return ProgInfo; }

void Elf32::setProgInfo(std::string ProgInfo) { this->ProgInfo = ProgInfo; }

std::string Elf32::getSectInfo() const { return SectInfo; }

void Elf32::setSectInfo(std::string SectInfo) { this->SectInfo = SectInfo; }

