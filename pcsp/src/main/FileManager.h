#pragma once
class FileManager 
{
   public:
    FileManager();
    FileManager(std::ifstream& f);
    void setActualFile(std::ifstream& f);
    void loadAndDefine(std::ifstream& f);
    std::ifstream& getActualFile();
    PBP &getPBP();
    PSPModuleInfo &getPSPModuleInfo();
    Elf32& getElf32();
    int getType();
    void processElf();
    void readElf32Header();
    void readElfProgramHeaders();
    void readElfSectionHeaders();
    u32 getBaseoffset();
    u32 getElfoffset() ;
    u32 getLoadAddressLow();
    u32 getLoadAddressHigh();
   private:
    void processPbp();
    Elf32SectionHeader* firstStep(Elf32Header ehdr, std::ifstream& f, std::vector<Elf32SectionHeader> sectionheaders);
};
