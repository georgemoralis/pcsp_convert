using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "Common.h"
#include "../Debugger/DisassemblerModule/syscalls.h"
#include "../Memory.h"
#include "Decoder.h"

namespace jpcsp::Allegrex
{
	using Processor = jpcsp::Processor;
	using Utilities = jpcsp::util::Utilities;
	using Syscallv15 = jpcsp::Syscallv15;

	void Common::Instruction::resetCount()
	{
		m_count = 0;
	}

	void Common::Instruction::increaseCount()
	{
		m_count++;
	}

	int Common::Instruction::getCount()
	{
		return m_count;
	}

	int Common::Instruction::count()
	{
		return m_count;
	}

	Common::Instruction *Common::Instruction::instance(int insn)
	{
		return this;
	}

	Common::Instruction::Instruction(int index)
	{
		jpcsp::Allegrex::Common::m_instances[index] = this;
	}

	Common::Instruction::Instruction()
	{
	}

	void Common::STUB::interpret(Processor *processor, int insn)
	{
		instance(insn)->interpret(processor, insn);
	}

	void Common::STUB::compile(Processor *processor, int insn)
	{
		instance(insn)->compile(processor, insn);
	}

	string Common::STUB::disasm(int address, int insn)
	{
		return instance(insn)->disasm(address, insn);
	}

	string Common::STUB::name()
	{
		return "";
	}

	string Common::STUB::category()
	{
		return "";
	}

const Instruction *Common::UNK = new InstructionAnonymousInnerClass();

	void Common::InstructionAnonymousInnerClass::interpret(Processor *processor, int insn)
	{
	}

	void Common::InstructionAnonymousInnerClass::compile(Processor *processor, int insn)
	{
	}

	string Common::InstructionAnonymousInnerClass::disasm(int address, int insn)
	{
		return String::format("Unknown instruction %32s (0x%08X)", Utilities::integerToBin(insn), insn);
	}

	string Common::InstructionAnonymousInnerClass::name()
	{
		return "UNK";
	}

	string Common::InstructionAnonymousInnerClass::category()
	{
		return "UNK";
	}

string *Common::gprNames = new string[32] {"$zr", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};
string *Common::fprNames = new string[32] {"$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$f6", "$f7", "$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15", "$f16", "$f17", "$f18", "$f19", "$f20", "$f21", "$f22", "$f23", "$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30", "$f31"};
string **Common::vprNames = new string[3]
{
	new string[128] {"S000.s", "S010.s", "S020.s", "S030.s", "S100.s", "S110.s", "S120.s", "S130.s", "S200.s", "S210.s", "S220.s", "S230.s", "S300.s", "S310.s", "S320.s", "S330.s", "S400.s", "S410.s", "S420.s", "S430.s", "S500.s", "S510.s", "S520.s", "S530.s", "S600.s", "S610.s", "S620.s", "S630.s", "S700.s", "S710.s", "S720.s", "S730.s", "S001.s", "S011.s", "S021.s", "S031.s", "S101.s", "S111.s", "S121.s", "S131.s", "S201.s", "S211.s", "S221.s", "S231.s", "S301.s", "S311.s", "S321.s", "S331.s", "S401.s", "S411.s", "S421.s", "S431.s", "S501.s", "S511.s", "S521.s", "S531.s", "S601.s", "S611.s", "S621.s", "S631.s", "S701.s", "S711.s", "S721.s", "S731.s", "S002.s", "S012.s", "S022.s", "S032.s", "S102.s", "S112.s", "S122.s", "S132.s", "S202.s", "S212.s", "S222.s", "S232.s", "S302.s", "S312.s", "S322.s", "S332.s", "S402.s", "S412.s", "S422.s", "S432.s", "S502.s", "S512.s", "S522.s", "S532.s", "S602.s", "S612.s", "S622.s", "S632.s", "S702.s", "S712.s", "S722.s", "S732.s", "S003.s", "S013.s", "S023.s", "S033.s", "S103.s", "S113.s", "S123.s", "S133.s", "S203.s", "S213.s", "S223.s", "S233.s", "S303.s", "S313.s", "S323.s", "S333.s", "S403.s", "S413.s", "S423.s", "S433.s", "S503.s", "S513.s", "S523.s", "S533.s", "S603.s", "S613.s", "S623.s", "S633.s", "S703.s", "S713.s", "S723.s", "S733.s"},
	new string[128] {"C000.p", "C010.p", "C020.p", "C030.p", "C100.p", "C110.p", "C120.p", "C130.p", "C200.p", "C210.p", "C220.p", "C230.p", "C300.p", "C310.p", "C320.p", "C330.p", "C400.p", "C410.p", "C420.p", "C430.p", "C500.p", "C510.p", "C520.p", "C530.p", "C600.p", "C610.p", "C620.p", "C630.p", "C700.p", "C710.p", "C720.p", "C730.p", "R000.p", "R001.p", "R002.p", "R003.p", "R100.p", "R101.p", "R102.p", "R103.p", "R200.p", "R201.p", "R202.p", "R203.p", "R300.p", "R301.p", "R302.p", "R303.p", "R400.p", "R401.p", "R402.p", "R403.p", "R500.p", "R501.p", "R502.p", "R503.p", "R600.p", "R601.p", "R602.p", "R603.p", "R700.p", "R701.p", "R702.p", "R703.p", "C002.p", "C012.p", "C022.p", "C032.p", "C102.p", "C112.p", "C122.p", "C132.p", "C202.p", "C212.p", "C222.p", "C232.p", "C302.p", "C312.p", "C322.p", "C332.p", "C402.p", "C412.p", "C422.p", "C432.p", "C502.p", "C512.p", "C522.p", "C532.p", "C602.p", "C612.p", "C622.p", "C632.p", "C702.p", "C712.p", "C722.p", "C732.p", "R020.p", "R021.p", "R022.p", "R023.p", "R120.p", "R121.p", "R122.p", "R123.p", "R220.p", "R221.p", "R222.p", "R223.p", "R320.p", "R321.p", "R322.p", "R323.p", "R420.p", "R421.p", "R422.p", "R423.p", "R520.p", "R521.p", "R522.p", "R523.p", "R620.p", "R621.p", "R622.p", "R623.p", "R720.p", "R721.p", "R722.p", "R723.p"},
	new string[128] {"C000.t", "C010.t", "C020.t", "C030.t", "C100.t", "C110.t", "C120.t", "C130.t", "C200.t", "C210.t", "C220.t", "C230.t", "C300.t", "C310.t", "C320.t", "C330.t", "C400.t", "C410.t", "C420.t", "C430.t", "C500.t", "C510.t", "C520.t", "C530.t", "C600.t", "C610.t", "C620.t", "C630.t", "C700.t", "C710.t", "C720.t", "C730.t", "R000.t", "R001.t", "R002.t", "R003.t", "R100.t", "R101.t", "R102.t", "R103.t", "R200.t", "R201.t", "R202.t", "R203.t", "R300.t", "R301.t", "R302.t", "R303.t", "R400.t", "R401.t", "R402.t", "R403.t", "R500.t", "R501.t", "R502.t", "R503.t", "R600.t", "R601.t", "R602.t", "R603.t", "R700.t", "R701.t", "R702.t", "R703.t", "C001.t", "C011.t", "C021.t", "C031.t", "C101.t", "C111.t", "C121.t", "C131.t", "C201.t", "C211.t", "C221.t", "C231.t", "C301.t", "C311.t", "C321.t", "C331.t", "C401.t", "C411.t", "C421.t", "C431.t", "C501.t", "C511.t", "C521.t", "C531.t", "C601.t", "C611.t", "C621.t", "C631.t", "C701.t", "C711.t", "C721.t", "C731.t", "R010.t", "R011.t", "R012.t", "R013.t", "R110.t", "R111.t", "R112.t", "R113.t", "R210.t", "R211.t", "R212.t", "R213.t", "R310.t", "R311.t", "R312.t", "R313.t", "R410.t", "R411.t", "R412.t", "R413.t", "R510.t", "R511.t", "R512.t", "R513.t", "R610.t", "R611.t", "R612.t", "R613.t", "R710.t", "R711.t", "R712.t", "R713.t"}
};
string *Common::fcrNames = new string[32] {"$fcsr0", "$fcsr1", "$fcsr2", "$fcsr3", "$fcsr4", "$fcsr5", "$fcsr6", "$fcsr7", "$fcsr8", "$fcsr9", "$fcsr10", "$fcsr11", "$fcsr12", "$fcsr13", "$fcsr14", "$fcsr15", "$fcsr16", "$fcsr17", "$fcsr18", "$fcsr19", "$fcsr20", "$fcsr21", "$fcsr22", "$fcsr23", "$fcsr24", "$fcsr25", "$fcsr26", "$fcsr27", "$fcsr28", "$fcsr29", "$fcsr30", "$fcsr31"};
string *Common::cop0Names = new string[32] {"Index", "Random", "EntryLo0", "EntryLo1", "Context", "PageMask", "Wired", "cop0reg7", "BadVaddr", "Count", "EntryHi", "Compare", "Status", "Cause", "EPC", "PrID", "Config", "LLAddr", "WatchLo", "WatchHi", "XContext", "cop0reg21", "cop0reg22", "cop0reg23", "cop0reg24", "EBase", "ECC", "CacheErr", "TagLo", "TagHi", "ErrorPC", "cop0reg31"};
string *Common::vsuffix = new string[4] {".s", ".p", ".t", ".q"};
const string *Common::ccondsNames = new string[16] {"c.f.s", "c.un.s", "c.eq.s", "c.ueq.s", "c.olt.s", "c.ult.s", "c.ole.s", "c.ule.s", "c.sf.s", "c.ngle.s", "c.seq.s", "c.ngl.s", "c.lt.s", "c.nge.s", "c.le.s", "c.ngt.s"};

	string Common::disasmRDRTSA(const string &opname, int rd, int rt, int sa)
	{
		if ((rd == 0) && sa == 0)
		{
			return "nop";
		}
		else
		{
			return String::format("%1$-10s %2$s, %3$s, 0x%4$04X", opname, gprNames[rd], gprNames[rt], sa);
		}
	}

	string Common::disasmRDRTRS(const string &opname, int rd, int rt, int rs)
	{
		return String::format("%1$-10s %2$s, %3$s, %4$s", opname, gprNames[rd], gprNames[rt], gprNames[rs]);
	}

	string Common::disasmRS(const string &opname, int rs)
	{
		return String::format("%1$-10s %2$s", opname, gprNames[rs]);
	}

	string Common::disasmRT(const string &opname, int rt)
	{
		return String::format("%1$-10s %2$s", opname, gprNames[rt]);
	}

	string Common::disasmRDRS(const string &opname, int rd, int rs)
	{
		return String::format("%1$-10s %2$s, %3$s", opname, gprNames[rd], gprNames[rs]);
	}

	string Common::disasmRDRT(const string &opname, int rd, int rt)
	{
		return String::format("%1$-10s %2$s, %3$s", opname, gprNames[rd], gprNames[rt]);
	}

	string Common::disasmRD(const string &opname, int rd)
	{
		return String::format("%1$-10s %2$s", opname, gprNames[rd]);
	}

	string Common::disasmRSRT(const string &opname, int rs, int rt)
	{
		return String::format("%1$-10s %2$s, %3$s", opname, gprNames[rs], gprNames[rt]);
	}

	string Common::disasmEXT(int rt, int rs, int rd, int sa)
	{
		return String::format("%1$-10s %2$s, %3$s, %4$d, %5$d", "ext", gprNames[rt], gprNames[rs], sa, (rd + 1));
	}

	string Common::disasmINS(int rt, int rs, int rd, int sa)
	{
		return String::format("%1$-10s %2$s, %3$s, %4$d, %5$d", "ins", gprNames[rt], gprNames[rs], sa, (rd - sa + 1));
	}

	string Common::disasmRDRSRT(const string &opname, int rd, int rs, int rt)
	{
		string s = String::format("%1$-10s %2$s, %3$s, %4$s", opname, gprNames[rd], gprNames[rs], gprNames[rt]);
		if (rs == 0 && rt == 0)
		{

			if (opname == "xor" || opname == "nor")
			{
				return StringHelper::formatSimple("%2$s <=> li %1$s, -1", gprNames[rd], s);
			}

			return StringHelper::formatSimple("%2$s <=> li %1$s, 0", gprNames[rd], s);
		}
		else if (rs == 0)
		{

			if (opname == "and")
			{
				return StringHelper::formatSimple("%2$s <=> li %1$s, 0", gprNames[rd], s);
			}

			if (opname == "nor")
			{
				return StringHelper::formatSimple("%2$s <=> not %1$s", gprNames[rd], s);
			}

			if (opname == "sub")
			{
				return StringHelper::formatSimple("%3$s <=> neg %1$s, %2$s", gprNames[rd], gprNames[rt], s);
			}

			if (opname == "subu")
			{
				return StringHelper::formatSimple("%3$s <=> negu %1$s, %2$s", gprNames[rd], gprNames[rt], s);
			}

			return StringHelper::formatSimple("%3$s <=> move %1$s, %2$s", gprNames[rd], gprNames[rt], s);
		}
		else if (rt == 0)
		{

			if (opname == "and")
			{
				return StringHelper::formatSimple("%2$s <=> li %1$s, 0", gprNames[rd], s);
			}

			if (opname == "nor")
			{
				return StringHelper::formatSimple("%2$s <=> not %1$s", gprNames[rd], gprNames[rs], s);
			}

			return StringHelper::formatSimple("%3$s <=> move %1$s, %2$s", gprNames[rd], gprNames[rs], s);
		}

		return s;
	}

	string Common::disasmRSOFFSET(const string &opname, int rs, int simm16, int opcode_address)
	{
		return String::format("%1$-10s %2$s, 0x%3$08X", opname, gprNames[rs], (static_cast<int>(static_cast<short>(simm16))) * 4 + opcode_address + 4);
	}

	string Common::disasmRSRTOFFSET(const string &opname, int rs, int rt, int simm16, int opcode_address)
	{
		return String::format("%1$-10s %2$s, %3$s, 0x%4$08X", opname, gprNames[rs], gprNames[rt], (static_cast<int>(static_cast<short>(simm16))) * 4 + opcode_address + 4);
	}

	string Common::disasmOFFSET(const string &opname, int simm16, int opcode_address)
	{
		return String::format("%1$-10s 0x%4$04X", opname, (static_cast<int>(static_cast<short>(simm16))) * 4 + opcode_address + 4);
	}


//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
