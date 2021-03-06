#include "PCSPCommon.h"
#include "Memory.h"
#include "MemoryMap.h"
#include "format/DeferredStub.h"
#include "format/Elf32SectionHeader.h"
#include "format/PBP.h"
#include "format/PSP.h"
#include "format/PSPModuleInfo.h"
#include "format/Elf32.h"
#include "FileManager.h"

std::string ElfInfo, ProgInfo, PbpInfo, SectInfo;  // TODO : think a better way

PSPModuleInfo moduleInfo;
PBP pbp;
Elf32 elf;
PSP psp;
std::ifstream *actualFile;
std::string filePath;
int type = -1;
u32 elfoffset = 0;
u32 baseoffset = 0;
u32 loadAddressLow, loadAddressHigh;  // The space consumed by the program image
std::list<DeferredStub> deferredImports;

/*TODO*/  //    private SeekableDataInput iso;

FileManager::FileManager() {}
FileManager::FileManager(std::ifstream &f) { loadAndDefine(f); }

/*TODO*/  //    public FileManager(SeekableDataInput iso)
/*TODO*/  //    {
/*TODO*/  //    }

PSPModuleInfo &FileManager::getPSPModuleInfo() { return moduleInfo; }

PBP &FileManager::getPBP() { return pbp; }
Elf32 &FileManager::getElf32() { return elf; }

std::ifstream &FileManager::getActualFile() { return *actualFile; }

void FileManager::setActualFile(std::ifstream &f) { actualFile = &f; }

void FileManager::loadAndDefine(std::ifstream &f) {
    setActualFile(f);
    elfoffset = 0;
    baseoffset = 0;

    loadAddressLow = 0;
    loadAddressHigh = 0;
    moduleInfo = PSPModuleInfo();
    deferredImports.clear();

    // makes sense put the more used first...

    /*try pbp format*/
    pbp = PBP(getActualFile());
    //           if (pbp.getOffsetParam() > 0)
    //                System.out.println(pbp.readPSF(getActualFile()));
    processPbp();
    if (getType() == FORMAT_PBP) {
        return;
    }
    /*end try pbp format*/

    /*try elf32 format*/
    elf = Elf32(getActualFile());
    processElf();
    if (getType() == FORMAT_ELF) {
        return;
    }
    /*end try elf32 format*/
}

int FileManager::getType() { return type; }

void FileManager::processElf() {
    if (getElf32().getHeader().isValid()) {
        type = FORMAT_ELF;
        readElf32Header();
        readElfProgramHeaders();
        readElfSectionHeaders();
    } else {
        printf("NOT AN ELF FILE\n");
    }
}
void FileManager::readElf32Header() {
    if (!getElf32().getHeader().isMIPSExecutable()) {
        printf("NOT A MIPS executable\n");
    }
    if (getElf32().getHeader().isPRXDetected()) {
        printf("PRX detected, requires relocation\n");
        baseoffset = 0x08900000;
    } else if (getElf32().getHeader().requiresRelocation()) {
        // seen in .elf's generated by pspsdk with BUILD_PRX=1 before conversion to .prx
        printf("ELF requires relocation\n");
        baseoffset = 0x08900000;
    }
    ElfInfo = getElf32().getElfInfo();
}

void FileManager::processPbp() {
    if (getPBP().isValid()) {
        /*TODO*/  //
        /*TODO*/  //            if (Settings.get_instance().readBoolOptions("emuoptions/pbpunpack")) {
        /*TODO*/  //                getPBP().unpackPBP(getActualFile());
        /*TODO*/  //            }
        elfoffset = getPBP().getOffsetPspData();
        getActualFile().seekg(elfoffset);  // seek the new offset

        PbpInfo = getPBP().toString();  // inteast this use PBP.getInfo()

        elf = Elf32(getActualFile());           // the elf of pbp
        if (!getElf32().getHeader().isValid())  // probably not an elf
        {
            getActualFile().seekg(elfoffset);  // seek again to elfoffset
            psp = PSP(getActualFile());
            if (psp.isValid())  // check if it is an encrypted file
            {
                printf("Encrypted psp format.Not Supported!\n");
                type = FORMAT_PSP;
                return;
            }
        }
        getPBP().setElf32(elf);  // composite the pbp...

        processElf();

        type = FORMAT_PBP;
    } else {
        elfoffset = 0;
        getActualFile().seekg(0);
        getPBP().setInfo("-----NOT A PBP FILE---------\n");
    }
}

void FileManager::readElfProgramHeaders() {
    std::vector<Elf32ProgramHeader> programheaders;

    for (int i = 0; i < getElf32().getHeader().getE_phnum(); i++) {
        getActualFile().seekg(
            (elfoffset + getElf32().getHeader().getE_phoff() + (i * getElf32().getHeader().getE_phentsize())));
        Elf32ProgramHeader phdr = Elf32ProgramHeader(getActualFile());
        programheaders.push_back(phdr);

        char tmp[128];
        sprintf(tmp, "-----PROGRAM HEADER #%02d-----\n", i);
        ProgInfo.append(tmp);
        ProgInfo.append(phdr.toString());
        // yapspd: if the PRX file is a kernel module then the most significant
        // bit must be set in the phsyical address of the first program header.
        if (i == 0 && (phdr.getP_paddr() & 0x80000000L) == 0x80000000) {
            // kernel mode prx
            printf("Kernel mode PRX detected\n");
        }

        getElf32().setProgInfo(ProgInfo);
        getElf32().setListProgramHeader(programheaders);
    }
}

void FileManager::readElfSectionHeaders() {
    std::vector<Elf32SectionHeader> sectionheaders;  // use in more than one step

    Elf32SectionHeader *shstrtab = NULL;  // use in more than one step
    shstrtab = firstStep(getElf32().getHeader(), getActualFile(), sectionheaders);
}

Elf32SectionHeader *FileManager::firstStep(Elf32Header ehdr, std::ifstream &f,
                                           std::vector<Elf32SectionHeader> &sectionheaders) {
    /** Read the ELF section headers (1st pass) */

    loadAddressLow = ((int)baseoffset > 0x08900000) ? (int)baseoffset : 0x08900000;
    loadAddressHigh = (int)baseoffset;

    Elf32SectionHeader *shstrtab = NULL;
    for (int i = 0; i < ehdr.getE_shnum(); i++) {
        f.seekg((int)(elfoffset + ehdr.getE_shoff() + (i * ehdr.getE_shentsize())));
        Elf32SectionHeader shdr = Elf32SectionHeader(f);
        sectionheaders.push_back(shdr);

        // Find the shstrtab
        if (shdr.getSh_type() == SHT_STRTAB && shstrtab == NULL)  // 0x00000003
        {
            shstrtab = &shdr;
        }
        u32 offsettoread = 0;
        if ((shdr.getSh_flags() & SHF_ALLOCATE) == SHF_ALLOCATE) {
            switch (shdr.getSh_type()) {
                case 1:  // ShType.PROGBITS
                {
                    /// System.out.println("FEED MEMORY WITH IT!");
                    f.seekg((elfoffset + shdr.getSh_offset()));
                    offsettoread = getBaseoffset() + shdr.getSh_addr();/* -MemoryMap::START_RAM*/;

                    /***************************************
                     * Load a block on main memory ....
                     ***************************************/
                    f.read((char *)Memory::getPointer(offsettoread), shdr.getSh_size());
                    if ((baseoffset + shdr.getSh_addr()) < loadAddressLow)
                        loadAddressLow = (int)(baseoffset + shdr.getSh_addr());
                    if ((baseoffset + shdr.getSh_addr() + shdr.getSh_size()) > loadAddressHigh)
                        loadAddressHigh = (int)(baseoffset + shdr.getSh_addr() + shdr.getSh_size());
                } break;
                case 8:  // ShType.NOBITS
                {
                    // System.out.println("NO BITS");
                    //  zero out this memory
                    offsettoread = (getBaseoffset() + shdr.getSh_addr() /* - MemoryMap::START_RAM*/);
                    memset(Memory::getPointer(offsettoread), 0, shdr.getSh_size());

                    if ((baseoffset + shdr.getSh_addr()) < loadAddressLow)
                        loadAddressLow = (baseoffset + shdr.getSh_addr());
                    if ((baseoffset + shdr.getSh_addr() + shdr.getSh_size()) > loadAddressHigh)
                        loadAddressHigh = (baseoffset + shdr.getSh_addr() + shdr.getSh_size());
                } break;
            }
        }
    }
    
            //System.out.println("load image low=" + Integer.toHexString(loadAddressLow)
            //            + " high=" + Integer.toHexString(loadAddressHigh) + "");
    getElf32().setListSectionHeader(sectionheaders);  // make the connection
                                                      
    //step 2 merged into step1
    // 
    // 2nd pass generate info string for the GUI and get module infos
    // moduleinfo = new PSPModuleInfo(); moved to loadAndDefine()
    int SectionCounter = 0;
    for (Elf32SectionHeader shdr : sectionheaders) {
        // Number the section
        char tmp[128];
        sprintf(tmp, "-----SECTION HEADER #%02d-----\n", SectionCounter);
        SectInfo.append(tmp);
        // Resolve section name (if possible)
        if (shstrtab != NULL) {
            f.seekg((elfoffset + shstrtab->getSh_offset() + shdr.getSh_name()));
            std::string SectionName;
            char c;
            f.read(&c, 1);
            while (c != 0) {
                SectionName.append(&c, 0, 1);
                f.read(&c, 1);
            }
            if (SectionName.length() > 0) {
                shdr.setSh_namez(SectionName);
                SectInfo.append(SectionName + "\n");
                // System.out.println(SectionName);
                // Get module infos
                if (SectionName.compare(".rodata.sceModuleInfo") == 0) {
                    f.seekg(((elfoffset + shdr.getSh_offset())));
                    getPSPModuleInfo().read(f);
                    // System.out.println(Long.toHexString(moduleinfo.m_gp));

                    printf("Found ModuleInfo name: %s version: %08x\n", getPSPModuleInfo().getM_namez().c_str(),
                           getPSPModuleInfo().getM_version());

                    if ((getPSPModuleInfo().getM_attr() & 0x1000) != 0) {
                        printf("Kernel mode module detected\n");
                    }
                    if ((getPSPModuleInfo().getM_attr() & 0x0800) != 0) {
                        printf("VSH mode module detected\n");
                    }
                }
            }
        }
        // Add this section header's info
        SectInfo.append(shdr.toString());
        SectionCounter++;
    }

    getElf32().setSectInfo(SectInfo);
    return shstrtab;
}

u32 FileManager::getBaseoffset() { return baseoffset; }

u32 FileManager::getElfoffset() {
      return elfoffset;
    }

u32 FileManager::getLoadAddressLow() {
        return loadAddressLow;
   }
u32 FileManager::getLoadAddressHigh() {
      return loadAddressHigh;
 }
/*TODO*/  //
/*TODO*/  //    // TODO process deferred imports each time a new module is loaded
/*TODO*/  //    public void addDeferredImports(List<DeferredStub> list) {
/*TODO*/  //        deferredImports.addAll(list);
/*TODO*/  //    }
/*TODO*/  //}
/*TODO*/  //
