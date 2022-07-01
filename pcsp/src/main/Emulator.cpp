#include "PCSPCommon.h"
#include "Emulator.h"
#include "format/PBP.h"
#include "FileManager.h"
/*TODO*/  //    public static String ElfInfo, ProgInfo, PbpInfo, SectInfo;
/*TODO*/  //    private static Processor cpu;
/*TODO*/  //    private static Controller controller;
FileManager romManager;
/*TODO*/  //    private boolean mediaImplemented = false;
/*TODO*/  //    private Thread mainThread;
/*TODO*/  //    public static boolean run = false;
/*TODO*/  //    public static boolean pause = false;
/*TODO*/  //    private static MainGUI gui;
/*TODO*/  //    private static DisassemblerFrame debugger;
/*TODO*/  //    private static MemoryViewer memview;
/*TODO*/  //
/*TODO*/  //    public static int[] textsection = new int[2];
/*TODO*/  //    public static int[] initsection = new int[2];
/*TODO*/  //    public static int[] finisection = new int[2];
/*TODO*/  //    public static int[] Stubtextsection = new int[2];
/*TODO*/  //
/*TODO*/  //    public Emulator(MainGUI gui) {
/*TODO*/  //        this.gui = gui;
/*TODO*/  //        cpu = new Processor();
/*TODO*/  //
/*TODO*/  //        controller = new Controller();
/*TODO*/  //        mainThread = new Thread(this);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void load(SeekableDataInput f) throws IOException {
/*TODO*/  //        initNewPsp();
/*TODO*/  //        romManager = new FileManager(f);
/*TODO*/  //        initElf32();
/*TODO*/  //
/*TODO*/  //        // Delete breakpoints and reset to PC
/*TODO*/  //        if (debugger != null) {
/*TODO*/  //            debugger.resetDebugger();
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
void Emulator::load(std::ifstream &f){
/*TODO*/  //        //  here load fileName, iso or etc...
        processLoading(f);
/*TODO*/  //        if (!mediaImplemented) {
/*TODO*/  //            throw new IOException("This kind of file format still not supported.");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // Delete breakpoints and reset to PC
/*TODO*/  //        if (debugger != null) {
/*TODO*/  //            debugger.resetDebugger();
/*TODO*/  //        }
}
void Emulator::processLoading(std::ifstream &f) {
    /*TODO*/  //        initNewPsp();
        romManager = FileManager(f);
/*TODO*/  //
/*TODO*/  //        switch (romManager.getType()) {
/*TODO*/  //            case FileManager.FORMAT_ELF:
/*TODO*/  //                initElf32();//RAM, CPU, GPU...
/*TODO*/  //                break;
/*TODO*/  //            case FileManager.FORMAT_ISO:
/*TODO*/  //                break;
/*TODO*/  //            case FileManager.FORMAT_PBP:
/*TODO*/  //                initPbp();//RAM, CPU, GPU...
/*TODO*/  //                break;
/*TODO*/  //            case FileManager.FORMAT_UMD:
/*TODO*/  //                break;
/*TODO*/  //            case FileManager.FORMAT_PSP:
/*TODO*/  //                break;
/*TODO*/  //            default:
/*TODO*/  //                throw new IOException("Is not an acceptable format, please choose the rigth file.");
/*TODO*/  //        }
}
/*TODO*/  //
/*TODO*/  //    //elf32 initElf32
/*TODO*/  //    private void initElf32() throws IOException {
/*TODO*/  //        mediaImplemented = true;
/*TODO*/  //        initRamBy(romManager.getElf32());
/*TODO*/  //        initCpuBy(romManager.getElf32());
/*TODO*/  //        initDebugWindowsByElf32();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void initPbp() throws IOException {
/*TODO*/  //        mediaImplemented = true;
/*TODO*/  //        initRamBy(romManager.getPBP().getElf32());
/*TODO*/  //        initCpuBy(romManager.getPBP().getElf32());
/*TODO*/  //        initDebugWindowsByPbp();
/*TODO*/  //        //RAM, CPU, GPU...
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void initRamBy(Elf32 elf) throws IOException {
/*TODO*/  //        // Relocation
/*TODO*/  //        if (elf.getHeader().requiresRelocation()) {
/*TODO*/  //            for (Elf32SectionHeader shdr : elf.getListSectionHeader()) {
/*TODO*/  //                if (shdr.getSh_type() == ShType.PRXREL.getValue() /*|| // 0x700000A0
/*TODO*/  //                        shdr.getSh_type() == ShType.REL.getValue()*/) // 0x00000009
/*TODO*/  //                {
/*TODO*/  //                    Elf32Relocate rel = new Elf32Relocate();
/*TODO*/  //                    romManager.getActualFile().position((int) (romManager.getElfoffset() +
          //                    shdr.getSh_offset()));
/*TODO*/  //
/*TODO*/  //                    int RelCount = (int) shdr.getSh_size() / Elf32Relocate.sizeof();
/*TODO*/  //                    System.out.println(shdr.getSh_namez() + ": relocating " + RelCount + " entries");
/*TODO*/  //
/*TODO*/  //                    int AHL = 0; // (AHI << 16) | (ALO & 0xFFFF)
/*TODO*/  //
/*TODO*/  //                    int HI_addr = 0; // We'll use this to relocate R_MIPS_HI16 when we get a R_MIPS_LO16
/*TODO*/  //
/*TODO*/  //                    // Relocation modes, only 1 is allowed at a time
/*TODO*/  //                    boolean external = true; // copied from soywiz/pspemulator
/*TODO*/  //
/*TODO*/  //                    boolean local = false;
/*TODO*/  //                    boolean _gp_disp = false;
/*TODO*/  //
/*TODO*/  //                    for (int i = 0; i < RelCount; i++) {
/*TODO*/  //                        rel.read(romManager.getActualFile());
/*TODO*/  //
/*TODO*/  //                        int R_TYPE = (int) (rel.getR_info() & 0xFF);
/*TODO*/  //                        int OFS_BASE = (int) ((rel.getR_info() >> 8) & 0xFF);
/*TODO*/  //                        int ADDR_BASE = (int) ((rel.getR_info() >> 16) & 0xFF);
/*TODO*/  //                        //System.out.println("type=" + R_TYPE + ",base=" + OFS_BASE + ",addr=" + ADDR_BASE +
          //                        "");
/*TODO*/  //
/*TODO*/  //                        int data = Memory.get_instance().read32((int) romManager.getBaseoffset() + (int)
          //                        rel.getR_offset());
/*TODO*/  //                        long result = 0; // Used to hold the result of relocation, OR this back into data
/*TODO*/  //
/*TODO*/  //                        // these are the addends?
/*TODO*/  //                        // SysV ABI MIPS quote: "Because MIPS uses only Elf32_Rel re-location entries, the
          //                        relocated field holds the addend."
/*TODO*/  //                        int half16 = data & 0x0000FFFF; // 31/07/08 unused (fiveofhearts)
/*TODO*/  //
/*TODO*/  //                        int word32 = data & 0xFFFFFFFF;
/*TODO*/  //                        int targ26 = data & 0x03FFFFFF;
/*TODO*/  //                        int hi16 = data & 0x0000FFFF;
/*TODO*/  //                        int lo16 = data & 0x0000FFFF;
/*TODO*/  //                        int rel16 = data & 0x0000FFFF;
/*TODO*/  //                        int lit16 = data & 0x0000FFFF; // 31/07/08 unused (fiveofhearts)
/*TODO*/  //
/*TODO*/  //                        int pc = data & 0x0000FFFF; // 31/07/08 unused (fiveofhearts)
/*TODO*/  //
/*TODO*/  //                        int A = 0; // addend
/*TODO*/  //                        // moved outside the loop so context is saved
/*TODO*/  //                        //int AHL = 0; // (AHI << 16) | (ALO & 0xFFFF)
/*TODO*/  //
/*TODO*/  //                        int P = (int) romManager.getBaseoffset() + (int) rel.getR_offset(); // address of
          //                        instruction being relocated? 31/07/08 unused when external=true (fiveofhearts)
/*TODO*/  //
/*TODO*/  //                        int S = (int) romManager.getBaseoffset(); // ? copied from soywiz/pspemulator, but
          //                        doesn't match the docs (fiveofhearts)
/*TODO*/  //
/*TODO*/  //                        int G = 0; // ? 31/07/08 unused (fiveofhearts)
/*TODO*/  //
/*TODO*/  //                        int GP = (int) romManager.getBaseoffset() + (int)
          //                        romManager.getPSPModuleInfo().getM_gp(); // final gp value, computed correctly?
          //                        31/07/08 only used in R_MIPS_GPREL16 which is untested (fiveofhearts)
/*TODO*/  //
/*TODO*/  //                        int GP0 = (int) romManager.getPSPModuleInfo().getM_gp(); // gp value, computed
          //                        correctly? 31/07/08 unused when external=true (fiveofhearts)
/*TODO*/  //
/*TODO*/  //                        int EA = 0; // ? 31/07/08 unused (fiveofhearts)
/*TODO*/  //
/*TODO*/  //                        int L = 0; // ? 31/07/08 unused (fiveofhearts)
/*TODO*/  //
/*TODO*/  //                        switch (R_TYPE) {
/*TODO*/  //                            case 0: //R_MIPS_NONE
/*TODO*/  //                                // Don't do anything
/*TODO*/  //
/*TODO*/  //                                break;
/*TODO*/  //
/*TODO*/  //                            case 5: //R_MIPS_HI16
/*TODO*/  //
/*TODO*/  //                                A = hi16;
/*TODO*/  //                                AHL = A << 16;
/*TODO*/  //                                HI_addr = (int) romManager.getBaseoffset() + (int) rel.getR_offset();
/*TODO*/  //                                break;
/*TODO*/  //
/*TODO*/  //                            case 6: //R_MIPS_LO16
/*TODO*/  //
/*TODO*/  //                                A = lo16;
/*TODO*/  //                                AHL &= ~0x0000FFFF; // delete lower bits, since many R_MIPS_LO16 can follow
          //                                one R_MIPS_HI16
/*TODO*/  //
/*TODO*/  //                                AHL |= A & 0x0000FFFF;
/*TODO*/  //
/*TODO*/  //                                if (external || local) {
/*TODO*/  //                                    result = AHL + S;
/*TODO*/  //                                    data &= ~0x0000FFFF;
/*TODO*/  //                                    data |= result & 0x0000FFFF; // truncate
/*TODO*/  //
/*TODO*/  //                                    // Process deferred R_MIPS_HI16
/*TODO*/  //                                    int data2 = Memory.get_instance().read32(HI_addr);
/*TODO*/  //                                    data2 &= ~0x0000FFFF;
/*TODO*/  //                                    data2 |= (result >> 16) & 0x0000FFFF; // truncate
/*TODO*/  //
/*TODO*/  //                                    Memory.get_instance().write32(HI_addr, data2);
/*TODO*/  //                                } else if (_gp_disp) {
/*TODO*/  //                                    result = AHL + GP - P + 4;
/*TODO*/  //
/*TODO*/  //                                    // verify
/*TODO*/  //                                    if ((result & ~0xFFFFFFFF) != 0) {
/*TODO*/  //                                        throw new IOException("Relocation overflow (R_MIPS_LO16)");
/*TODO*/  //                                    }
/*TODO*/  //                                    data &= ~0x0000FFFF;
/*TODO*/  //                                    data |= result & 0x0000FFFF;
/*TODO*/  //
/*TODO*/  //                                    // Process deferred R_MIPS_HI16
/*TODO*/  //                                    int data2 = Memory.get_instance().read32(HI_addr);
/*TODO*/  //
/*TODO*/  //                                    result = AHL + GP - P;
/*TODO*/  //
/*TODO*/  //                                    // verify
/*TODO*/  //                                    if ((result & ~0xFFFFFFFF) != 0) {
/*TODO*/  //                                        throw new IOException("Relocation overflow (R_MIPS_HI16)");
/*TODO*/  //                                    }
/*TODO*/  //                                    data2 &= ~0x0000FFFF;
/*TODO*/  //                                    data2 |= (result >> 16) & 0x0000FFFF;
/*TODO*/  //                                    Memory.get_instance().write32(HI_addr, data2);
/*TODO*/  //                                }
/*TODO*/  //                                break;
/*TODO*/  //
/*TODO*/  //                            case 4: //R_MIPS_26
/*TODO*/  //
/*TODO*/  //                                if (local) {
/*TODO*/  //                                    A = targ26;
/*TODO*/  //                                    result = ((A << 2) | (P & 0xf0000000) + S) >> 2;
/*TODO*/  //                                    data &= ~0x03FFFFFF;
/*TODO*/  //                                    data |= (int) (result & 0x03FFFFFF); // truncate
/*TODO*/  //
/*TODO*/  //                                } else if (external) {
/*TODO*/  //                                    A = targ26;
/*TODO*/  //
/*TODO*/  //                                    // docs say "sign-extend(A < 2)", but is it meant to be A << 2? if so
          //                                    then there's no point sign extending
/*TODO*/  //                                    //result = (sign-extend(A < 2) + S) >> 2;
/*TODO*/  //                                    //result = (((A < 2) ? 0xFFFFFFFF : 0x00000000) + S) >> 2;
/*TODO*/  //                                    result = ((A << 2) + S) >> 2; // copied from soywiz/pspemulator
/*TODO*/  //
/*TODO*/  //                                    data &= ~0x03FFFFFF;
/*TODO*/  //                                    data |= (int) (result & 0x03FFFFFF); // truncate
/*TODO*/  //
/*TODO*/  //                                }
/*TODO*/  //                                break;
/*TODO*/  //
/*TODO*/  //                            case 2: //R_MIPS_32
/*TODO*/  //                                // This doesn't match soywiz/pspemulator but it generates more sensible
          //                                addresses (fiveofhearts)
/*TODO*/  //
/*TODO*/  //                                A = word32;
/*TODO*/  //                                result = S + A;
/*TODO*/  //                                data &= ~0xFFFFFFFF;
/*TODO*/  //                                data |= (int) (result & 0xFFFFFFFF); // truncate
/*TODO*/  //
/*TODO*/  //                                break;
/*TODO*/  //
/*TODO*/  //                            /* sample before relocation: 0x00015020: 0x8F828008 '....' - lw         $v0,
          //                            -32760($gp)
/*TODO*/  //                            case 7: //R_MIPS_GPREL16
/*TODO*/  //                                // 31/07/08 untested (fiveofhearts)
/*TODO*/  //                                System.out.println("Untested relocation type " + R_TYPE + " at " +
          //                                String.format("%08x", (int)baseoffset + (int)rel.r_offset));
/*TODO*/  //
/*TODO*/  //                                if (external)
/*TODO*/  //                                {
/*TODO*/  //                                    A = rel16;
/*TODO*/  //
/*TODO*/  //                                    //result = sign-extend(A) + S + GP;
/*TODO*/  //                                    result = (((A & 0x00008000) != 0) ? A & 0xFFFF0000 : A) + S + GP;
/*TODO*/  //
/*TODO*/  //                                    // verify
/*TODO*/  //                                    if ((result & ~0x0000FFFF) != 0)
/*TODO*/  //                                        throw new IOException("Relocation overflow (R_MIPS_GPREL16)");
/*TODO*/  //
/*TODO*/  //                                    data &= ~0x0000FFFF;
/*TODO*/  //                                    data |= (int)(result & 0x0000FFFF);
/*TODO*/  //                                }
/*TODO*/  //                                else if (local)
/*TODO*/  //                                {
/*TODO*/  //                                    A = rel16;
/*TODO*/  //
/*TODO*/  //                                    //result = sign-extend(A) + S + GP;
/*TODO*/  //                                    result = (((A & 0x00008000) != 0) ? A & 0xFFFF0000 : A) + S + GP0 - GP;
/*TODO*/  //
/*TODO*/  //                                    // verify
/*TODO*/  //                                    if ((result & ~0x0000FFFF) != 0)
/*TODO*/  //                                        throw new IOException("Relocation overflow (R_MIPS_GPREL16)");
/*TODO*/  //
/*TODO*/  //                                    data &= ~0x0000FFFF;
/*TODO*/  //                                    data |= (int)(result & 0x0000FFFF);
/*TODO*/  //                                }
/*TODO*/  //                                break;
/*TODO*/  //                             */
/*TODO*/  //                            default:
/*TODO*/  //                                System.out.println("Unhandled relocation type " + R_TYPE + " at " +
          //                                String.format("%08x", (int) romManager.getBaseoffset() + (int)
          //                                rel.getR_offset()));
/*TODO*/  //                                break;
/*TODO*/  //                        }
/*TODO*/  //
/*TODO*/  //                        //System.out.println("Relocation type " + R_TYPE + " at " + String.format("%08x",
          //                        (int)baseoffset + (int)rel.r_offset));
/*TODO*/  //                        Memory.get_instance().write32((int) romManager.getBaseoffset() + (int)
          //                        rel.getR_offset(), data);
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //        int numberoffailedNIDS = 0;
/*TODO*/  //        int numberofmappedNIDS = 0;
/*TODO*/  //        // Imports
/*TODO*/  //        for (Elf32SectionHeader shdr : elf.getListSectionHeader()) {
/*TODO*/  //            if (shdr.getSh_namez().equals(".lib.stub")) {
/*TODO*/  //                Memory mem = Memory.get_instance();
/*TODO*/  //                int stubHeadersAddress = (int) (romManager.getBaseoffset() + shdr.getSh_addr());
/*TODO*/  //                int stubHeadersCount = (int) (shdr.getSh_size() / Elf32StubHeader.sizeof());
/*TODO*/  //
/*TODO*/  //                Elf32StubHeader stubHeader;
/*TODO*/  //                List<DeferredStub> deferred = new LinkedList<DeferredStub>();
/*TODO*/  //                NIDMapper nidMapper = NIDMapper.get_instance();
/*TODO*/  //
/*TODO*/  //                //System.out.println(shdr.getSh_namez() + ":" + stubsCount + " module entries");
/*TODO*/  //                for (int i = 0; i < stubHeadersCount; i++) {
/*TODO*/  //                    stubHeader = new Elf32StubHeader(mem, stubHeadersAddress);
/*TODO*/  //                    stubHeader.setModuleNamez(readStringZ(mem.mainmemory, (int)
          //                    (stubHeader.getOffsetModuleName() - MemoryMap.START_RAM)));
/*TODO*/  //                    stubHeadersAddress += Elf32StubHeader.sizeof(); //stubHeader.s_size * 4;
/*TODO*/  //                    //System.out.println(stubHeader.toString());
/*TODO*/  //
/*TODO*/  //                    for (int j = 0; j < stubHeader.getImports(); j++) {
/*TODO*/  //                        int nid = mem.read32((int) (stubHeader.getOffsetNid() + j * 4));
/*TODO*/  //                        int importAddress = (int) (stubHeader.getOffsetText() + j * 8);
/*TODO*/  //                        int exportAddress;
/*TODO*/  //                        int code;
/*TODO*/  //
/*TODO*/  //                        // Attempt to fixup stub to point to an already loaded module export
/*TODO*/  //                        exportAddress = nidMapper.moduleNidToAddress(stubHeader.getModuleNamez(), nid);
/*TODO*/  //                        if (exportAddress != -1) {
/*TODO*/  //                            int instruction
/*TODO*/  //                                    = // j <jumpAddress>
/*TODO*/  //                                    ((jpcsp.AllegrexOpcodes.J & 0x3f) << 26)
/*TODO*/  //                                    | ((exportAddress >>> 2) & 0x03ffffff);
/*TODO*/  //
/*TODO*/  //                            mem.write32(importAddress, instruction);
/*TODO*/  //
/*TODO*/  //                            System.out.println("Mapped NID " + Integer.toHexString(nid) + " to export");
/*TODO*/  //                        } // Attempt to fixup stub to known syscalls
/*TODO*/  //                        else {
/*TODO*/  //                            code = nidMapper.nidToSyscall(nid);
/*TODO*/  //                            if (code != -1) {
/*TODO*/  //                                // Fixup stub, replacing nop with syscall
/*TODO*/  //                                int instruction
/*TODO*/  //                                        = // syscall <code>
/*TODO*/  //                                        ((jpcsp.AllegrexOpcodes.SPECIAL & 0x3f) << 26)
/*TODO*/  //                                        | (jpcsp.AllegrexOpcodes.SYSCALL & 0x3f)
/*TODO*/  //                                        | ((code & 0x000fffff) << 6);
/*TODO*/  //
/*TODO*/  //                                mem.write32(importAddress + 4, instruction);
/*TODO*/  //                                numberofmappedNIDS++;
/*TODO*/  //                                //System.out.println("Mapped NID " + Integer.toHexString(nid) + " to syscall
          //                                " + Integer.toHexString(code));
/*TODO*/  //                            } else {
/*TODO*/  //                                // Save nid for deferred fixup
/*TODO*/  //                                deferred.add(new DeferredStub(stubHeader.getModuleNamez(), importAddress,
          //                                nid));
/*TODO*/  //                                System.out.println("Failed to map NID " + Integer.toHexString(nid) + " (load
          //                                time)");
/*TODO*/  //                                numberoffailedNIDS++;
/*TODO*/  //                            }
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                romManager.addDeferredImports(deferred);
/*TODO*/  //            }
/*TODO*/  //            //the following are used for the instruction counter panel
/*TODO*/  //            if (shdr.getSh_namez().equals(".text")) {
/*TODO*/  //                textsection[0] = (int) (romManager.getBaseoffset() + shdr.getSh_addr());
/*TODO*/  //                textsection[1] = (int) shdr.getSh_size();
/*TODO*/  //            }
/*TODO*/  //            if (shdr.getSh_namez().equals(".init")) {
/*TODO*/  //                initsection[0] = (int) (romManager.getBaseoffset() + shdr.getSh_addr());
/*TODO*/  //                initsection[1] = (int) shdr.getSh_size();
/*TODO*/  //            }
/*TODO*/  //            if (shdr.getSh_namez().equals(".fini")) {
/*TODO*/  //                finisection[0] = (int) (romManager.getBaseoffset() + shdr.getSh_addr());
/*TODO*/  //                finisection[1] = (int) shdr.getSh_size();
/*TODO*/  //            }
/*TODO*/  //            if (shdr.getSh_namez().equals(".sceStub.text")) {
/*TODO*/  //                Stubtextsection[0] = (int) (romManager.getBaseoffset() + shdr.getSh_addr());
/*TODO*/  //                Stubtextsection[1] = (int) shdr.getSh_size();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            //test the instruction counter
/*TODO*/  //            //if (/*shdr.getSh_namez().equals(".text") || */shdr.getSh_namez().equals(".init") /*||
          //            shdr.getSh_namez().equals(".fini")*/) {
/*TODO*/  //            /*
/*TODO*/  //               int sectionAddress = (int)(romManager.getBaseoffset() + shdr.getSh_addr());
/*TODO*/  //               System.out.println(Integer.toHexString(sectionAddress) + " size = " + shdr.getSh_size());
/*TODO*/  //               for(int i =0; i< shdr.getSh_size(); i+=4)
/*TODO*/  //               {
/*TODO*/  //                 int memread32 = Memory.get_instance().read32(sectionAddress+i);
/*TODO*/  //                 //System.out.println(memread32);
/*TODO*/  //                 jpcsp.Allegrex.Decoder.instruction(memread32).increaseCount();
/*TODO*/  //               }
/*TODO*/  //
/*TODO*/  //
/*TODO*/  //            }
/*TODO*/  //            System.out.println(jpcsp.Allegrex.Instructions.ADDIU.getCount());*/
/*TODO*/  //        }
/*TODO*/  //        System.out.println(numberofmappedNIDS + " NIDS mapped");
/*TODO*/  //        if (numberoffailedNIDS > 0) {
/*TODO*/  //            System.out.println("Total Failed to map NIDS = " + numberoffailedNIDS);
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void initCpuBy(Elf32 elf) {
/*TODO*/  //        //set the default values for registers not sure if they are correct and UNTESTED!!
/*TODO*/  //        //some settings from soywiz/pspemulator
/*TODO*/  //        cpu.pc = (int) romManager.getBaseoffset() + (int) elf.getHeader().getE_entry(); //set the pc
          //        register.
/*TODO*/  //        cpu.npc = cpu.pc + 4;
/*TODO*/  //        cpu.gpr[4] = 0; //a0
/*TODO*/  //        cpu.gpr[5] = (int) romManager.getBaseoffset() + (int) elf.getHeader().getE_entry(); //
          //        argumentsPointer a1 reg
/*TODO*/  //        cpu.gpr[6] = 0; //a2
/*TODO*/  //        cpu.gpr[26] = 0x09F00000; //k0
/*TODO*/  //        cpu.gpr[27] = 0; //k1 should probably be 0
/*TODO*/  //        cpu.gpr[28] = (int) romManager.getBaseoffset() + (int) romManager.getPSPModuleInfo().getM_gp(); //gp
          //        reg    gp register should get the GlobalPointer!!!
/*TODO*/  //        cpu.gpr[29] = 0x09F00000; //sp
/*TODO*/  //        cpu.gpr[31] = 0x08000004; //ra, should this be 0?
/*TODO*/  //        // All other registers are uninitialised/random values
/*TODO*/  //
/*TODO*/  //        jpcsp.HLE.pspSysMem.get_instance().Initialise(romManager.getLoadAddressLow(),
          //        romManager.getLoadAddressHigh() - romManager.getLoadAddressLow());
/*TODO*/  //        jpcsp.HLE.ThreadMan.get_instance().Initialise(cpu.pc, romManager.getPSPModuleInfo().getM_attr());
/*TODO*/  //        jpcsp.HLE.psputils.get_instance().Initialise();
/*TODO*/  //        jpcsp.HLE.pspge.get_instance().Initialise();
/*TODO*/  //        jpcsp.HLE.pspdisplay.get_instance().Initialise();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void initDebugWindowsByPbp() {
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void initDebugWindowsByElf32() {
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void initNewPsp() {
/*TODO*/  //        getProcessor().reset();
/*TODO*/  //        Memory.get_instance().NullMemory();
/*TODO*/  //        NIDMapper.get_instance().Initialise();
/*TODO*/  //
/*TODO*/  //        if (memview != null) {
/*TODO*/  //            memview.RefreshMemory();
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @Override
/*TODO*/  //    public void run() {
/*TODO*/  //        while (true) {
/*TODO*/  //            try {
/*TODO*/  //                synchronized (this) {
/*TODO*/  //                    while (pause) {
/*TODO*/  //                        wait();
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //            } catch (InterruptedException e) {
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            cpu.step();
/*TODO*/  //            jpcsp.HLE.ThreadMan.get_instance().step();
/*TODO*/  //            jpcsp.HLE.pspdisplay.get_instance().step();
/*TODO*/  //            controller.checkControllerState();
/*TODO*/  //
/*TODO*/  //            if (debugger != null) {
/*TODO*/  //                debugger.step();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public synchronized void RunEmu() {
/*TODO*/  //        if (!mediaImplemented) {
/*TODO*/  //            return;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (pause) {
/*TODO*/  //            pause = false;
/*TODO*/  //            notify();
/*TODO*/  //        } else if (!run) {
/*TODO*/  //            run = true;
/*TODO*/  //            mainThread.start();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        gui.RefreshButtons();
/*TODO*/  //        if (debugger != null) {
/*TODO*/  //            debugger.RefreshButtons();
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // static so Memory can pause emu on invalid read/write
/*TODO*/  //    public static synchronized void PauseEmu() {
/*TODO*/  //        if (run && !pause) {
/*TODO*/  //            pause = true;
/*TODO*/  //
/*TODO*/  //            gui.RefreshButtons();
/*TODO*/  //
/*TODO*/  //            if (debugger != null) {
/*TODO*/  //                debugger.RefreshButtons();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (memview != null) {
/*TODO*/  //                memview.RefreshMemory();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static void setFpsTitle(String fps) {
/*TODO*/  //        gui.setMainTitle(fps);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static Processor getProcessor() {
/*TODO*/  //        return cpu;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static Memory getMemory() {
/*TODO*/  //        return Memory.get_instance();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static Controller getController() {
/*TODO*/  //        return controller;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void setDebugger(DisassemblerFrame debugger) {
/*TODO*/  //        this.debugger = debugger;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void setMemoryViewer(MemoryViewer memview) {
/*TODO*/  //        this.memview = memview;
/*TODO*/  //    }
/*TODO*/  //}
