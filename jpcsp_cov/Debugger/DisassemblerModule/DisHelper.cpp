using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "DisHelper.h"
#include "syscalls.h"
#include "DisasmOpcodes.h"
#include "../../Memory.h"

namespace jpcsp::Debugger::DisassemblerModule
{

	int DisHelper::signExtend(int value)
	{
		return (value << 16) >> 16;
	}

	int DisHelper::signExtend8(int value)
	{
		return (value << 24) >> 24;
	}

	int DisHelper::zeroExtend(int value)
	{
		return (value & 0xffff);
	}

	int DisHelper::zeroExtend8(int value)
	{
		return (value & 0xff);
	}

string *DisHelper::gprNames = new string[32] {"$zr", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};
string *DisHelper::fprNames = new string[32] {"$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$f6", "$f7", "$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15", "$f16", "$f17", "$f18", "$f19", "$f20", "$f21", "$f22", "$f23", "$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30", "$f31"};
string **DisHelper::vprNames = new string[3]
{
	new string[128] {"S000.s", "S010.s", "S020.s", "S030.s", "S100.s", "S110.s", "S120.s", "S130.s", "S200.s", "S210.s", "S220.s", "S230.s", "S300.s", "S310.s", "S320.s", "S330.s", "S400.s", "S410.s", "S420.s", "S430.s", "S500.s", "S510.s", "S520.s", "S530.s", "S600.s", "S610.s", "S620.s", "S630.s", "S700.s", "S710.s", "S720.s", "S730.s", "S001.s", "S011.s", "S021.s", "S031.s", "S101.s", "S111.s", "S121.s", "S131.s", "S201.s", "S211.s", "S221.s", "S231.s", "S301.s", "S311.s", "S321.s", "S331.s", "S401.s", "S411.s", "S421.s", "S431.s", "S501.s", "S511.s", "S521.s", "S531.s", "S601.s", "S611.s", "S621.s", "S631.s", "S701.s", "S711.s", "S721.s", "S731.s", "S002.s", "S012.s", "S022.s", "S032.s", "S102.s", "S112.s", "S122.s", "S132.s", "S202.s", "S212.s", "S222.s", "S232.s", "S302.s", "S312.s", "S322.s", "S332.s", "S402.s", "S412.s", "S422.s", "S432.s", "S502.s", "S512.s", "S522.s", "S532.s", "S602.s", "S612.s", "S622.s", "S632.s", "S702.s", "S712.s", "S722.s", "S732.s", "S003.s", "S013.s", "S023.s", "S033.s", "S103.s", "S113.s", "S123.s", "S133.s", "S203.s", "S213.s", "S223.s", "S233.s", "S303.s", "S313.s", "S323.s", "S333.s", "S403.s", "S413.s", "S423.s", "S433.s", "S503.s", "S513.s", "S523.s", "S533.s", "S603.s", "S613.s", "S623.s", "S633.s", "S703.s", "S713.s", "S723.s", "S733.s"},
	new string[128] {"C000.p", "C010.p", "C020.p", "C030.p", "C100.p", "C110.p", "C120.p", "C130.p", "C200.p", "C210.p", "C220.p", "C230.p", "C300.p", "C310.p", "C320.p", "C330.p", "C400.p", "C410.p", "C420.p", "C430.p", "C500.p", "C510.p", "C520.p", "C530.p", "C600.p", "C610.p", "C620.p", "C630.p", "C700.p", "C710.p", "C720.p", "C730.p", "R000.p", "R001.p", "R002.p", "R003.p", "R100.p", "R101.p", "R102.p", "R103.p", "R200.p", "R201.p", "R202.p", "R203.p", "R300.p", "R301.p", "R302.p", "R303.p", "R400.p", "R401.p", "R402.p", "R403.p", "R500.p", "R501.p", "R502.p", "R503.p", "R600.p", "R601.p", "R602.p", "R603.p", "R700.p", "R701.p", "R702.p", "R703.p", "C002.p", "C012.p", "C022.p", "C032.p", "C102.p", "C112.p", "C122.p", "C132.p", "C202.p", "C212.p", "C222.p", "C232.p", "C302.p", "C312.p", "C322.p", "C332.p", "C402.p", "C412.p", "C422.p", "C432.p", "C502.p", "C512.p", "C522.p", "C532.p", "C602.p", "C612.p", "C622.p", "C632.p", "C702.p", "C712.p", "C722.p", "C732.p", "R020.p", "R021.p", "R022.p", "R023.p", "R120.p", "R121.p", "R122.p", "R123.p", "R220.p", "R221.p", "R222.p", "R223.p", "R320.p", "R321.p", "R322.p", "R323.p", "R420.p", "R421.p", "R422.p", "R423.p", "R520.p", "R521.p", "R522.p", "R523.p", "R620.p", "R621.p", "R622.p", "R623.p", "R720.p", "R721.p", "R722.p", "R723.p"},
	new string[128] {"C000.t", "C010.t", "C020.t", "C030.t", "C100.t", "C110.t", "C120.t", "C130.t", "C200.t", "C210.t", "C220.t", "C230.t", "C300.t", "C310.t", "C320.t", "C330.t", "C400.t", "C410.t", "C420.t", "C430.t", "C500.t", "C510.t", "C520.t", "C530.t", "C600.t", "C610.t", "C620.t", "C630.t", "C700.t", "C710.t", "C720.t", "C730.t", "R000.t", "R001.t", "R002.t", "R003.t", "R100.t", "R101.t", "R102.t", "R103.t", "R200.t", "R201.t", "R202.t", "R203.t", "R300.t", "R301.t", "R302.t", "R303.t", "R400.t", "R401.t", "R402.t", "R403.t", "R500.t", "R501.t", "R502.t", "R503.t", "R600.t", "R601.t", "R602.t", "R603.t", "R700.t", "R701.t", "R702.t", "R703.t", "C001.t", "C011.t", "C021.t", "C031.t", "C101.t", "C111.t", "C121.t", "C131.t", "C201.t", "C211.t", "C221.t", "C231.t", "C301.t", "C311.t", "C321.t", "C331.t", "C401.t", "C411.t", "C421.t", "C431.t", "C501.t", "C511.t", "C521.t", "C531.t", "C601.t", "C611.t", "C621.t", "C631.t", "C701.t", "C711.t", "C721.t", "C731.t", "R010.t", "R011.t", "R012.t", "R013.t", "R110.t", "R111.t", "R112.t", "R113.t", "R210.t", "R211.t", "R212.t", "R213.t", "R310.t", "R311.t", "R312.t", "R313.t", "R410.t", "R411.t", "R412.t", "R413.t", "R510.t", "R511.t", "R512.t", "R513.t", "R610.t", "R611.t", "R612.t", "R613.t", "R710.t", "R711.t", "R712.t", "R713.t"}
};
string *DisHelper::fcrNames = new string[32] {"$fcsr0", "$fcsr1", "$fcsr2", "$fcsr3", "$fcsr4", "$fcsr5", "$fcsr6", "$fcsr7", "$fcsr8", "$fcsr9", "$fcsr10", "$fcsr11", "$fcsr12", "$fcsr13", "$fcsr14", "$fcsr15", "$fcsr16", "$fcsr17", "$fcsr18", "$fcsr19", "$fcsr20", "$fcsr21", "$fcsr22", "$fcsr23", "$fcsr24", "$fcsr25", "$fcsr26", "$fcsr27", "$fcsr28", "$fcsr29", "$fcsr30", "$fcsr31"};
string *DisHelper::cop0Names = new string[32] {"Index", "Random", "EntryLo0", "EntryLo1", "Context", "PageMask", "Wired", "cop0reg7", "BadVaddr", "Count", "EntryHi", "Compare", "Status", "Cause", "EPC", "PrID", "Config", "LLAddr", "WatchLo", "WatchHi", "XContext", "cop0reg21", "cop0reg22", "cop0reg23", "cop0reg24", "EBase", "ECC", "CacheErr", "TagLo", "TagHi", "ErrorPC", "cop0reg31"};
string *DisHelper::vsuffix = new string[4] {".s", ".p", ".t", ".q"};
const string *DisHelper::ccondsNames = new string[16] {"c.f.s", "c.un.s", "c.eq.s", "c.ueq.s", "c.olt.s", "c.ult.s", "c.ole.s", "c.ule.s", "c.sf.s", "c.ngle.s", "c.seq.s", "c.ngl.s", "c.lt.s", "c.nge.s", "c.le.s", "c.ngt.s"};

	string DisHelper::Dis_RDRTSA(const string &opname, int rd, int rt, int sa)
	{
		if ((rd == 0) && sa == 0)
		{
			return "nop";
		}
		else
		{
			return opname + " " + gprNames[rd] + ", " + gprNames[rt] + ", " + to_string(sa);
		}
	}

	string DisHelper::Dis_RDRTRS(const string &opname, int rd, int rt, int rs)
	{
		//TODO CHECK IF rt  rs  =0
		return opname + " " + gprNames[rd] + ", " + gprNames[rt] + ", " + gprNames[rs];
	}

	string DisHelper::Dis_RS(const string &opname, int rs)
	{
		return opname + " " + gprNames[rs];
	}

	string DisHelper::Dis_RT(const string &opname, int rt)
	{
		return opname + " " + gprNames[rt];
	}

	string DisHelper::Dis_RDRS(const string &opname, int rd, int rs)
	{
		return opname + " " + gprNames[rd] + ", " + gprNames[rs];
	}

	string DisHelper::Dis_RDRT(const string &opname, int rd, int rt)
	{
		return opname + " " + gprNames[rd] + ", " + gprNames[rt];
	}

	string DisHelper::Dis_RD(const string &opname, int rd)
	{
		return opname + " " + gprNames[rd];
	}

	string DisHelper::Dis_RSRT(const string &opname, int rs, int rt)
	{
		return opname + " " + gprNames[rs] + ", " + gprNames[rt];
	}

	string DisHelper::Dis_Ext(int rt, int rs, int rd, int sa)
	{
		return "ext " + gprNames[rt] + ", " + gprNames[rs] + ", " + to_string(sa) + ", " + to_string(rd + 1);
	}

	string DisHelper::Dis_Ins(int rt, int rs, int rd, int sa)
	{
		return "ins " + gprNames[rt] + ", " + gprNames[rs] + ", " + to_string(sa) + ", " + to_string(rd - sa + 1);
	}

	string DisHelper::Dis_RDRSRT(const string &opname, int rd, int rs, int rt)
	{
		if (rs == 0 && rt == 0)
		{

			if (opname == "xor" || opname == "nor")
			{
				return "li " + gprNames[rd] + ", -1";
			}

			return "li " + gprNames[rd] + ", 0";

		}
		else if (rs == 0)
		{

			if (opname == "and")
			{
				return "li " + gprNames[rd] + ", 0";
			}

			if (opname == "nor")
			{
				return "not " + gprNames[rd] + ", " + gprNames[rt];
			}

			if (regex_match(opname, regex("sub")))
			{
				return "neg " + gprNames[rd] + ", " + gprNames[rt];
			}

			return "move " + gprNames[rd] + ", " + gprNames[rs];

		}
		else if (rt == 0)
		{

			if (opname == "and")
			{
				return "li " + gprNames[rd] + ", 0";
			}

			if (opname == "nor")
			{
				return "not " + gprNames[rd] + ", " + gprNames[rs];
			}

			return "move " + gprNames[rd] + ", " + gprNames[rs];

		}

		return opname + " " + gprNames[rd] + ", " + gprNames[rs] + ", " + gprNames[rt];
	}

	string DisHelper::Dis_RSOFFSET(const string &opname, int rs, int simm16, int opcode_address)
	{
		return opname + " " + gprNames[rs] + ", 0x" + Integer::toHexString(simm16 * 4 + opcode_address + 4);
	}

	string DisHelper::Dis_RSRTOFFSET(const string &opname, int rs, int rt, int simm16, int opcode_address)
	{
		return opname + " " + gprNames[rs] + ", " + gprNames[rt] + ", 0x" + Integer::toHexString(simm16 * 4 + opcode_address + 4);
	}

	string DisHelper::Dis_OFFSET(const string &opname, int imm, int opcode_address)
	{
		return opname + " 0x" + Integer::toHexString(imm * 4 + opcode_address + 4);
	}

	string DisHelper::Dis_RTRSIMM(const string &opname, int rt, int rs, int imm16)
	{

		/* if (!opname.equals("andi") && !opname.equals("ori") && !opname.equals("xori")) {
		imm = (imm << 16) >> 16;
		} NOT Needed??? */

		if (rs == 0)
		{

			if (opname == "andi")
			{
				return "li " + gprNames[rt] + ", 0";
			}
			else if (regex_match(opname, regex("slti")))
			{
				return "li " + gprNames[rt] + ", " + to_string((0 < imm16) ? 1 : 0);
			}

		}

		return opname + " " + gprNames[rt] + ", " + gprNames[rs] + ", " + to_string(imm16);
	}

	string DisHelper::Dis_Syscall(int code)
	{ // probably okay
		string s = string();
		for (syscalls::calls c : syscalls::callsHelper::values())
		{
			if (c.getValue() == code)
			{
				s = "syscall " + Integer::toHexString(code) + "     " + c;
				return s;

			}
		}
		s = "syscall 0x" + Integer::toHexString(code) + " [unknown]";
		return s;
	}

	string DisHelper::Dis_Break(int code)
	{
		return "break 0x" + Integer::toHexString(code);
	}

	string DisHelper::Dis_JUMP(const string &opname, int uimm26, int opcode_address)
	{
		int jump = (opcode_address & 0xf0000000) | ((uimm26 & 0x3ffffff) << 2);

		// If we think the target is a stub try and append the syscall name
		if (opname == "jal" && jump != 0)
		{
			DisasmOpcodes *disOp = new DisasmOpcodes();
			string secondTarget = disOp->disasm(jpcsp::Memory::get_instance()->read32(jump + 4), jump + 4);
			if (secondTarget.starts_with("syscall") && secondTarget.find("[unknown]") == string::npos)
			{
				delete disOp;
				return opname + " 0x" + Integer::toHexString(jump) + " " + secondTarget.substr(13);
			}

			delete disOp;
		}

		return opname + " 0x" + Integer::toHexString(jump);
	}

	string DisHelper::Dis_RTIMM(const string &opname, int rt, int imm)
	{
		return opname + " " + gprNames[rt] + ", " + to_string(imm);
	}


//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
