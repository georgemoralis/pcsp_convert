using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "DisasmOpcodes.h"
#include "DisHelper.h"

namespace jpcsp::Debugger::DisassemblerModule
{
	using namespace jpcsp::Debugger::DisassemblerModule;
//	import static jpcsp.Debugger.DisassemblerModule.DisHelper.*;
	using AllegrexInstructions = jpcsp::AllegrexInstructions;
	using AllegrexDecoder = jpcsp::AllegrexDecoder;

	string DisasmOpcodes::disasm(int value, int opcode_address)
	{
		this->opcode_address = opcode_address;
		returnString = "Unsupported Instruction";
		disasm_Conflict->process(this, value);
		return returnString;
	}

	void DisasmOpcodes::doUNK(const string &reason)
	{
		returnString = reason;
	}

	void DisasmOpcodes::doNOP()
	{
		returnString = "nop";
	}

	void DisasmOpcodes::doSLL(int rd, int rt, int sa)
	{
		returnString = DisHelper::Dis_RDRTSA("sll", rd, rt, sa);
	}

	void DisasmOpcodes::doSRL(int rd, int rt, int sa)
	{
		returnString = DisHelper::Dis_RDRTSA("srl", rd, rt, sa);
	}

	void DisasmOpcodes::doSRA(int rd, int rt, int sa)
	{
		returnString = DisHelper::Dis_RDRTSA("sra", rd, rt, sa);
	}

	void DisasmOpcodes::doSLLV(int rd, int rt, int rs)
	{
		returnString = DisHelper::Dis_RDRTRS("sllv", rd, rt, rs);
	}

	void DisasmOpcodes::doSRLV(int rd, int rt, int rs)
	{
		returnString = DisHelper::Dis_RDRTRS("srlv", rd, rt, rs);
	}

	void DisasmOpcodes::doSRAV(int rd, int rt, int rs)
	{
		returnString = DisHelper::Dis_RDRTRS("srav", rd, rt, rs);
	}

	void DisasmOpcodes::doJR(int rs)
	{
		returnString = DisHelper::Dis_RS("jr", rs);
	}

	void DisasmOpcodes::doJALR(int rd, int rs)
	{
		returnString = DisHelper::Dis_RDRS("jalr", rd, rs);
	}

	void DisasmOpcodes::doMFHI(int rd)
	{
		returnString = DisHelper::Dis_RD("mfhi", rd);
	}

	void DisasmOpcodes::doMTHI(int rs)
	{
		returnString = DisHelper::Dis_RS("mthi", rs);
	}

	void DisasmOpcodes::doMFLO(int rd)
	{
		returnString = DisHelper::Dis_RD("mflo", rd);
	}

	void DisasmOpcodes::doMTLO(int rs)
	{
		returnString = DisHelper::Dis_RS("mtlo", rs);
	}

	void DisasmOpcodes::doMULT(int rs, int rt)
	{
		returnString = DisHelper::Dis_RSRT("mult", rs, rt);
	}

	void DisasmOpcodes::doMULTU(int rs, int rt)
	{
		returnString = DisHelper::Dis_RSRT("multu", rs, rt);
	}

	void DisasmOpcodes::doDIV(int rs, int rt)
	{
		returnString = DisHelper::Dis_RSRT("div", rs, rt);
	}

	void DisasmOpcodes::doDIVU(int rs, int rt)
	{
		returnString = DisHelper::Dis_RSRT("divu", rs, rt);
	}

	void DisasmOpcodes::doADD(int rd, int rs, int rt)
	{
		returnString = DisHelper::Dis_RDRSRT("add", rd, rs, rt);
	}

	void DisasmOpcodes::doADDU(int rd, int rs, int rt)
	{
		returnString = DisHelper::Dis_RDRSRT("addu", rd, rs, rt);
	}

	void DisasmOpcodes::doSUB(int rd, int rs, int rt)
	{
		returnString = DisHelper::Dis_RDRSRT("sub", rd, rs, rt);
	}

	void DisasmOpcodes::doSUBU(int rd, int rs, int rt)
	{
		returnString = DisHelper::Dis_RDRSRT("subu", rd, rs, rt);
	}

	void DisasmOpcodes::doAND(int rd, int rs, int rt)
	{
		returnString = DisHelper::Dis_RDRSRT("and", rd, rs, rt);
	}

	void DisasmOpcodes::doOR(int rd, int rs, int rt)
	{
		returnString = DisHelper::Dis_RDRSRT("or", rd, rs, rt);
	}

	void DisasmOpcodes::doXOR(int rd, int rs, int rt)
	{
		returnString = DisHelper::Dis_RDRSRT("xor", rd, rs, rt);
	}

	void DisasmOpcodes::doNOR(int rd, int rs, int rt)
	{
		returnString = DisHelper::Dis_RDRSRT("nor", rd, rs, rt);
	}

	void DisasmOpcodes::doSLT(int rd, int rs, int rt)
	{
		returnString = DisHelper::Dis_RDRSRT("slt", rd, rs, rt);
	}

	void DisasmOpcodes::doSLTU(int rd, int rs, int rt)
	{
		returnString = DisHelper::Dis_RDRSRT("sltu", rd, rs, rt);
	}

	void DisasmOpcodes::doBLTZ(int rs, int simm16)
	{
		returnString = DisHelper::Dis_RSOFFSET("bltz", rs, simm16, opcode_address);
	}

	void DisasmOpcodes::doBGEZ(int rs, int simm16)
	{
		returnString = DisHelper::Dis_RSOFFSET("bgez", rs, simm16, opcode_address);
	}

	void DisasmOpcodes::doBLTZL(int rs, int simm16)
	{
		returnString = DisHelper::Dis_RSOFFSET("bltzl", rs, simm16, opcode_address);
	}

	void DisasmOpcodes::doBGEZL(int rs, int simm16)
	{
		returnString = DisHelper::Dis_RSOFFSET("bgezl", rs, simm16, opcode_address);
	}

	void DisasmOpcodes::doBLTZAL(int rs, int simm16)
	{
		returnString = DisHelper::Dis_RSOFFSET("bltzal", rs, simm16, opcode_address);
	}

	void DisasmOpcodes::doBGEZAL(int rs, int simm16)
	{
		returnString = DisHelper::Dis_RSOFFSET("bgezal", rs, simm16, opcode_address);
	}

	void DisasmOpcodes::doBLTZALL(int rs, int simm16)
	{
		returnString = DisHelper::Dis_RSOFFSET("bltzall", rs, simm16, opcode_address);
	}

	void DisasmOpcodes::doBGEZALL(int rs, int simm16)
	{
		returnString = DisHelper::Dis_RSOFFSET("bgezall", rs, simm16, opcode_address);
	}

	void DisasmOpcodes::doJ(int uimm26)
	{
		returnString = DisHelper::Dis_JUMP("j", uimm26, opcode_address);
	}

	void DisasmOpcodes::doJAL(int uimm26)
	{
		returnString = DisHelper::Dis_JUMP("jal", uimm26, opcode_address);
	}

	void DisasmOpcodes::doBEQ(int rs, int rt, int simm16)
	{
		returnString = DisHelper::Dis_RSRTOFFSET("beq", rs, rt, simm16, opcode_address);
	}

	void DisasmOpcodes::doBNE(int rs, int rt, int simm16)
	{
		returnString = DisHelper::Dis_RSRTOFFSET("bne", rs, rt, simm16, opcode_address);
	}

	void DisasmOpcodes::doBLEZ(int rs, int simm16)
	{
		returnString = DisHelper::Dis_RSOFFSET("blez", rs, simm16, opcode_address);
	}

	void DisasmOpcodes::doBGTZ(int rs, int simm16)
	{
		returnString = DisHelper::Dis_RSOFFSET("bgtz", rs, simm16, opcode_address);
	}

	void DisasmOpcodes::doBEQL(int rs, int rt, int simm16)
	{
		returnString = DisHelper::Dis_RSRTOFFSET("beql", rs, rt, simm16, opcode_address);
	}

	void DisasmOpcodes::doBNEL(int rs, int rt, int simm16)
	{
		returnString = DisHelper::Dis_RSRTOFFSET("bnel", rs, rt, simm16, opcode_address);
	}

	void DisasmOpcodes::doBLEZL(int rs, int simm16)
	{
		returnString = DisHelper::Dis_RSOFFSET("blezl", rs, simm16, opcode_address);
	}

	void DisasmOpcodes::doBGTZL(int rs, int simm16)
	{

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
