#include "PCSPCommon.h"
#include "format/PBP.h"
#include "FileManager.h"

/*TODO*/  // public class FileManager {
/*TODO*/  //    public static String ElfInfo, ProgInfo, PbpInfo, SectInfo; // TODO : think a better way
/*TODO*/  //
/*TODO*/  //    private PSPModuleInfo moduleInfo;
PBP pbp;
/*TODO*/  //    private Elf32 elf;
/*TODO*/  //    private PSP psp;
std::ifstream *actualFile;
/*TODO*/  //    private String filePath;
/*TODO*/  //    public final static int FORMAT_ELF = 0;
/*TODO*/  //    public final static int FORMAT_PBP = 10;
/*TODO*/  //    public final static int FORMAT_UMD = 20;
/*TODO*/  //    public final static int FORMAT_ISO = 30;
/*TODO*/  //    public final static int FORMAT_PSP = 40;
/*TODO*/  //    private int type = -1;
u32 elfoffset = 0;
u32 baseoffset = 0;
u32 loadAddressLow, loadAddressHigh; // The space consumed by the program image
/*TODO*/  //    private List<DeferredStub> deferredImports;
/*TODO*/  //    private SeekableDataInput iso;

FileManager::FileManager() {}
FileManager::FileManager(std::ifstream &f) { 
    loadAndDefine(f);
}
/*TODO*/  //    public FileManager(SeekableDataInput iso)
/*TODO*/  //    {
/*TODO*/  //    }
/*TODO*/  //    public PSPModuleInfo getPSPModuleInfo() {
/*TODO*/  //        return moduleInfo;
/*TODO*/  //    }
/*TODO*/  //
PBP &FileManager::getPBP() {
    return pbp;
 }
/*TODO*/  //
/*TODO*/  //    public Elf32 getElf32() {
/*TODO*/  //        return elf;
/*TODO*/  //    }
/*TODO*/  //
std::ifstream &FileManager::getActualFile() {
        return *actualFile;
}

void FileManager::setActualFile(std::ifstream& f) {
    actualFile = &f;
}

void FileManager::loadAndDefine(std::ifstream& f) {
    setActualFile(f);
    elfoffset = 0;
    baseoffset = 0;

    loadAddressLow = 0;
    loadAddressHigh = 0;
/*TODO*/  //
/*TODO*/  //            moduleInfo = new PSPModuleInfo();
/*TODO*/  //            deferredImports = new LinkedList<DeferredStub>();
/*TODO*/  //
           //makes sense put the more used first...

            /*try pbp format*/
            pbp = PBP(getActualFile());
//           if (pbp.getOffsetParam() > 0)
//                System.out.println(pbp.readPSF(getActualFile()));
            processPbp();
/*TODO*/  //            if (getType() == FORMAT_PBP) {
/*TODO*/  //                return;
/*TODO*/  //            }
/*TODO*/  //            /*end try pbp format*/
/*TODO*/  //
/*TODO*/  //            /*try elf32 format*/
/*TODO*/  //            elf = new Elf32(getActualFile());
/*TODO*/  //            processElf();
/*TODO*/  //            if (getType() == FORMAT_ELF) {
/*TODO*/  //                return;
/*TODO*/  //            }
/*TODO*/  //            /*end try elf32 format*/
/*TODO*/  //
/*TODO*/  //
/*TODO*/  //            /*try xxxx format*/
/*TODO*/  //            /*try xxxx format*/
/*TODO*/  //
/*TODO*/  //
/*TODO*/  //            //NONE FORMAT SELECTED OR DETECTED :(
/*TODO*/  //        } finally {
/*TODO*/  //            // f.close(); // close or let it open...
/*TODO*/  //        }
    }
/*TODO*/  //
/*TODO*/  //    public int getType() {
/*TODO*/  //        return type;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void processElf() throws IOException {
/*TODO*/  //        if (getElf32().getHeader().isValid()) {
/*TODO*/  //            type = FORMAT_ELF;
/*TODO*/  //            readElf32Header();
/*TODO*/  //            readElfProgramHeaders();
/*TODO*/  //            readElfSectionHeaders();
/*TODO*/  //        } else {
/*TODO*/  //            System.out.println("NOT AN ELF FILE");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void readElf32Header() {
/*TODO*/  //        if (!getElf32().getHeader().isMIPSExecutable()) {
/*TODO*/  //            System.out.println("NOT A MIPS executable");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (getElf32().getHeader().isPRXDetected()) {
/*TODO*/  //            System.out.println("PRX detected, requires relocation");
/*TODO*/  //            baseoffset = 0x08900000;
/*TODO*/  //        } else if (getElf32().getHeader().requiresRelocation()) {
/*TODO*/  //            // seen in .elf's generated by pspsdk with BUILD_PRX=1 before conversion to .prx
/*TODO*/  //            System.out.println("ELF requires relocation");
/*TODO*/  //            baseoffset = 0x08900000;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        ElfInfo = getElf32().getElfInfo();
/*TODO*/  //    }
/*TODO*/  //
void FileManager::processPbp() {
    if (getPBP().isValid()) {
/*TODO*/  //
/*TODO*/  //            if (Settings.get_instance().readBoolOptions("emuoptions/pbpunpack")) {
/*TODO*/  //                getPBP().unpackPBP(getActualFile());
/*TODO*/  //            }
           elfoffset = getPBP().getOffsetPspData();
           getActualFile().seekg(elfoffset); //seek the new offset

/*TODO*/  //            PbpInfo = getPBP().toString(); //inteast this use PBP.getInfo()
/*TODO*/  //
/*TODO*/  //            elf = new Elf32(getActualFile()); //the elf of pbp
/*TODO*/  //            if(!getElf32().getHeader().isValid())//probably not an elf
/*TODO*/  //            {
/*TODO*/  //              getActualFile().position((int)elfoffset); //seek again to elfoffset
/*TODO*/  //              psp = new PSP(getActualFile());
/*TODO*/  //              if(psp.isValid())//check if it is an encrypted file
/*TODO*/  //              {
/*TODO*/  //                  System.out.println("Encrypted psp format.Not Supported!");
/*TODO*/  //                  type=FORMAT_PSP;
/*TODO*/  //                  return;
/*TODO*/  //              }
/*TODO*/  //            }
/*TODO*/  //            getPBP().setElf32(elf); //composite the pbp...
/*TODO*/  //
/*TODO*/  //            processElf();
/*TODO*/  //
/*TODO*/  //            type = FORMAT_PBP;
    } else {
/*TODO*/  //            elfoffset = 0;
/*TODO*/  //            getActualFile().position(0);
/*TODO*/  //            getPBP().setInfo("-----NOT A PBP FILE---------\n");
    }
}
/*TODO*/  //
/*TODO*/  //    private void readElfProgramHeaders() throws IOException {
/*TODO*/  //        List<Elf32ProgramHeader> programheaders = new LinkedList<Elf32ProgramHeader>();
/*TODO*/  //        StringBuffer phsb = new StringBuffer();
/*TODO*/  //
/*TODO*/  //        for (int i = 0; i < getElf32().getHeader().getE_phnum(); i++) {
/*TODO*/  //            getActualFile().position((int)(elfoffset + getElf32().getHeader().getE_phoff() + (i *
          //            getElf32().getHeader().getE_phentsize())));
/*TODO*/  //            Elf32ProgramHeader phdr = new Elf32ProgramHeader(getActualFile());
/*TODO*/  //            programheaders.add(phdr);
/*TODO*/  //
/*TODO*/  //            phsb.append("-----PROGRAM HEADER #" + i + "-----" + "\n");
/*TODO*/  //            phsb.append(phdr.toString());
/*TODO*/  //
/*TODO*/  //            // yapspd: if the PRX file is a kernel module then the most significant
/*TODO*/  //            // bit must be set in the phsyical address of the first program header.
/*TODO*/  //            if (i == 0 && (phdr.getP_paddr() & 0x80000000L) == 0x80000000L) {
/*TODO*/  //                // kernel mode prx
/*TODO*/  //                System.out.println("Kernel mode PRX detected");
/*TODO*/  //            }
/*TODO*/  //            ProgInfo = phsb.toString();
/*TODO*/  //
/*TODO*/  //            getElf32().setProgInfo(ProgInfo);
/*TODO*/  //            getElf32().setListProgramHeader(programheaders);
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void readElfSectionHeaders() throws IOException {
/*TODO*/  //        List<Elf32SectionHeader> sectionheaders = new LinkedList<Elf32SectionHeader>(); //use in more than
          //        one step
/*TODO*/  //
/*TODO*/  //        Elf32SectionHeader shstrtab = null; //use in more than one step
/*TODO*/  //
/*TODO*/  //        shstrtab = firstStep(getElf32().getHeader(), getActualFile(), sectionheaders);
/*TODO*/  //        secondStep(sectionheaders, shstrtab, getActualFile(), getPSPModuleInfo());
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private Elf32SectionHeader firstStep(Elf32Header ehdr, ByteBuffer f, List<Elf32SectionHeader>
          //    sectionheaders) throws IOException {
/*TODO*/  //        /** Read the ELF section headers (1st pass) */
/*TODO*/  //        getElf32().setListSectionHeader(sectionheaders); //make the connection
/*TODO*/  //
/*TODO*/  //        loadAddressLow = ((int)baseoffset > 0x08900000) ? (int)baseoffset : 0x08900000;
/*TODO*/  //        loadAddressHigh = (int)baseoffset;
/*TODO*/  //
/*TODO*/  //        Elf32SectionHeader shstrtab = null;
/*TODO*/  //        for (int i = 0; i < ehdr.getE_shnum(); i++) {
/*TODO*/  //            f.position((int)(elfoffset + ehdr.getE_shoff() + (i * ehdr.getE_shentsize())));
/*TODO*/  //            Elf32SectionHeader shdr = new Elf32SectionHeader(f);
/*TODO*/  //            sectionheaders.add(shdr);
/*TODO*/  //
/*TODO*/  //            // Find the shstrtab
/*TODO*/  //            if (shdr.getSh_type() == ShType.STRTAB.getValue() && shstrtab == null) // 0x00000003
/*TODO*/  //            {
/*TODO*/  //                shstrtab = shdr;
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            // Load some sections into memory
/*TODO*/  //            if ((shdr.getSh_flags() & ShFlags.Allocate.getValue()) == ShFlags.Allocate.getValue()) {
/*TODO*/  //                switch (shdr.getSh_type()) {
/*TODO*/  //                    case 1: //ShType.PROGBITS
/*TODO*/  //                        ///System.out.println("FEED MEMORY WITH IT!");
/*TODO*/  //
/*TODO*/  //                        f.position((int)(elfoffset + shdr.getSh_offset()));
/*TODO*/  //                        int offsettoread = (int) getBaseoffset() + (int) shdr.getSh_addr() -
          //                        MemoryMap.START_RAM;
/*TODO*/  //
/*TODO*/  //                        /***************************************
/*TODO*/  //                         * Load a block on main memory ....
/*TODO*/  //                         ***************************************/
/*TODO*/  //                        Utilities.copyByteBuffertoByteBuffer(f, Memory.get_instance().mainmemory,
          //                        offsettoread, (int) shdr.getSh_size());
/*TODO*/  //
/*TODO*/  //                        if ((int)(baseoffset + shdr.getSh_addr()) < loadAddressLow)
/*TODO*/  //                            loadAddressLow = (int)(baseoffset + shdr.getSh_addr());
/*TODO*/  //                        if ((int)(baseoffset + shdr.getSh_addr() + shdr.getSh_size()) > loadAddressHigh)
/*TODO*/  //                            loadAddressHigh = (int)(baseoffset + shdr.getSh_addr() + shdr.getSh_size());
/*TODO*/  //                        break;
/*TODO*/  //                    case 8: // ShType.NOBITS
/*TODO*/  //                        //System.out.println("NO BITS");
/*TODO*/  //                        // zero out this memory
/*TODO*/  //                        offsettoread = (int)(getBaseoffset() + shdr.getSh_addr() - MemoryMap.START_RAM);
/*TODO*/  //                        ByteBuffer mainmemory = Memory.get_instance().mainmemory;
/*TODO*/  //                        for (int j = 0; j < (int)shdr.getSh_size(); j++)
/*TODO*/  //                            mainmemory.put(offsettoread + j, (byte)0);
/*TODO*/  //
/*TODO*/  //                        if ((int)(baseoffset + shdr.getSh_addr()) < loadAddressLow)
/*TODO*/  //                            loadAddressLow = (int)(baseoffset + shdr.getSh_addr());
/*TODO*/  //                        if ((int)(baseoffset + shdr.getSh_addr() + shdr.getSh_size()) > loadAddressHigh)
/*TODO*/  //                            loadAddressHigh = (int)(baseoffset + shdr.getSh_addr() + shdr.getSh_size());
/*TODO*/  //                        break;
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        //System.out.println("load image low=" + Integer.toHexString(loadAddressLow)
/*TODO*/  //        //            + " high=" + Integer.toHexString(loadAddressHigh) + "");
/*TODO*/  //
/*TODO*/  //        return shstrtab;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void secondStep(List<Elf32SectionHeader> sectionheaders, Elf32SectionHeader shstrtab, ByteBuffer
          //    f, PSPModuleInfo moduleinfo) throws IOException {
/*TODO*/  //        // 2nd pass generate info string for the GUI and get module infos
/*TODO*/  //        //moduleinfo = new PSPModuleInfo(); moved to loadAndDefine()
/*TODO*/  //        StringBuffer shsb = new StringBuffer();
/*TODO*/  //        int SectionCounter = 0;
/*TODO*/  //        for (Elf32SectionHeader shdr : sectionheaders) {
/*TODO*/  //            // Number the section
/*TODO*/  //            shsb.append("-----SECTION HEADER #" + SectionCounter + "-----" + "\n");
/*TODO*/  //
/*TODO*/  //            // Resolve section name (if possible)
/*TODO*/  //            if (shstrtab != null) {
/*TODO*/  //                f.position((int)(elfoffset + shstrtab.getSh_offset() + shdr.getSh_name()));
/*TODO*/  //                String SectionName = "";//Utilities.readStringZ(f);
/*TODO*/  //               try{
/*TODO*/  //                    SectionName = Utilities.readStringZ(f);
/*TODO*/  //
/*TODO*/  //                }
/*TODO*/  //                catch(IOException e){
/*TODO*/  //                    System.out.println("ERROR:SectionNames can't be found.NIDs can't be load");
/*TODO*/  //                }
/*TODO*/  //                if (SectionName.length() > 0) {
/*TODO*/  //
/*TODO*/  //                    shdr.setSh_namez(SectionName);
/*TODO*/  //                    shsb.append(SectionName + "\n");
/*TODO*/  //                    //System.out.println(SectionName);
/*TODO*/  //                    // Get module infos
/*TODO*/  //                    if (SectionName.matches(".rodata.sceModuleInfo")) {
/*TODO*/  //                        f.position((int)((elfoffset + shdr.getSh_offset())));
/*TODO*/  //                        moduleinfo.read(f);
/*TODO*/  //                        //System.out.println(Long.toHexString(moduleinfo.m_gp));
/*TODO*/  //
/*TODO*/  //                        System.out.println("Found ModuleInfo name:'" + moduleinfo.getM_namez() + "'
          //                        version:" + Utilities.formatString("short",
          //                        Integer.toHexString(moduleinfo.getM_version() & 0xFFFF).toUpperCase()));
/*TODO*/  //
/*TODO*/  //                        if ((moduleinfo.getM_attr() & 0x1000) != 0) {
/*TODO*/  //                            System.out.println("Kernel mode module detected");
/*TODO*/  //                        }
/*TODO*/  //                        if ((moduleinfo.getM_attr() & 0x0800) != 0) {
/*TODO*/  //                            System.out.println("VSH mode module detected");
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //            // Add this section header's info
/*TODO*/  //            shsb.append(shdr.toString());
/*TODO*/  //            SectionCounter++;
/*TODO*/  //        }
/*TODO*/  //        SectInfo = shsb.toString();
/*TODO*/  //
/*TODO*/  //        getElf32().setSectInfo(SectInfo);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public long getBaseoffset() {
/*TODO*/  //        return baseoffset;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public long getElfoffset() {
/*TODO*/  //        return elfoffset;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getLoadAddressLow() {
/*TODO*/  //        return loadAddressLow;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getLoadAddressHigh() {
/*TODO*/  //        return loadAddressHigh;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // TODO process deferred imports each time a new module is loaded
/*TODO*/  //    public void addDeferredImports(List<DeferredStub> list) {
/*TODO*/  //        deferredImports.addAll(list);
/*TODO*/  //    }
/*TODO*/  //}
/*TODO*/  //