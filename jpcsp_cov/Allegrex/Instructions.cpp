using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "Instructions.h"
#include "../Debugger/DisassemblerModule/DisHelper.h"
#include "CpuState.h"
#include "FpuState.h"

namespace jpcsp::Allegrex
{
	using Processor = jpcsp::Processor;
	using namespace jpcsp::Debugger::DisassemblerModule;
//	import static jpcsp.Debugger.DisassemblerModule.DisHelper.*;
const Instruction *Instructions::NOP = new InstructionAnonymousInnerClass();

	Instructions::InstructionAnonymousInnerClass::InstructionAnonymousInnerClass() : Instruction(0)
	{
	}

	string Instructions::InstructionAnonymousInnerClass::name()
	{
		return "NOP";
	}

	string Instructions::InstructionAnonymousInnerClass::category()
	{
		return "MIPS I";
	}

	void Instructions::InstructionAnonymousInnerClass::interpret(Processor *processor, int insn)
	{


	}

	void Instructions::InstructionAnonymousInnerClass::compile(Processor *processor, int insn)
	{


	}

	string Instructions::InstructionAnonymousInnerClass::disasm(int address, int insn)
	{

	return "nop";
	}

const Instruction *Instructions::ICACHE_INDEX_INVALIDATE = new InstructionAnonymousInnerClass2();

	Instructions::InstructionAnonymousInnerClass2::InstructionAnonymousInnerClass2() : Instruction(1)
	{
	}

	string Instructions::InstructionAnonymousInnerClass2::name()
	{
		return "CACHE 0x04";
	}

	string Instructions::InstructionAnonymousInnerClass2::category()
	{
		return "ALLEGREX";
	}

	void Instructions::InstructionAnonymousInnerClass2::interpret(Processor *processor, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;


	}

	void Instructions::InstructionAnonymousInnerClass2::compile(Processor *processor, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;


	}

	string Instructions::InstructionAnonymousInnerClass2::disasm(int address, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;

	return Common::disasmCODEIMMRS("cache", 0x04, DisHelper::signExtend(imm16), rs);
	}

const Instruction *Instructions::ICACHE_INDEX_UNLOCK = new InstructionAnonymousInnerClass3();

	Instructions::InstructionAnonymousInnerClass3::InstructionAnonymousInnerClass3() : Instruction(2)
	{
	}

	string Instructions::InstructionAnonymousInnerClass3::name()
	{
		return "CACHE 0x06";
	}

	string Instructions::InstructionAnonymousInnerClass3::category()
	{
		return "ALLEGREX";
	}

	void Instructions::InstructionAnonymousInnerClass3::interpret(Processor *processor, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;


	}

	void Instructions::InstructionAnonymousInnerClass3::compile(Processor *processor, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;


	}

	string Instructions::InstructionAnonymousInnerClass3::disasm(int address, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;

	return Common::disasmCODEIMMRS("cache", 0x06, DisHelper::signExtend(imm16), rs);
	}

const Instruction *Instructions::ICACHE_HIT_INVALIDATE = new InstructionAnonymousInnerClass4();

	Instructions::InstructionAnonymousInnerClass4::InstructionAnonymousInnerClass4() : Instruction(3)
	{
	}

	string Instructions::InstructionAnonymousInnerClass4::name()
	{
		return "CACHE 0x08";
	}

	string Instructions::InstructionAnonymousInnerClass4::category()
	{
		return "ALLEGREX";
	}

	void Instructions::InstructionAnonymousInnerClass4::interpret(Processor *processor, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;


	}

	void Instructions::InstructionAnonymousInnerClass4::compile(Processor *processor, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;


	}

	string Instructions::InstructionAnonymousInnerClass4::disasm(int address, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;

	return Common::disasmCODEIMMRS("cache", 0x08, DisHelper::signExtend(imm16), rs);
	}

const Instruction *Instructions::ICACHE_FILL = new InstructionAnonymousInnerClass5();

	Instructions::InstructionAnonymousInnerClass5::InstructionAnonymousInnerClass5() : Instruction(4)
	{
	}

	string Instructions::InstructionAnonymousInnerClass5::name()
	{
		return "CACHE 0x0A";
	}

	string Instructions::InstructionAnonymousInnerClass5::category()
	{
		return "ALLEGREX";
	}

	void Instructions::InstructionAnonymousInnerClass5::interpret(Processor *processor, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;


	}

	void Instructions::InstructionAnonymousInnerClass5::compile(Processor *processor, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;


	}

	string Instructions::InstructionAnonymousInnerClass5::disasm(int address, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;

	return Common::disasmCODEIMMRS("cache", 0x0A, DisHelper::signExtend(imm16), rs);
	}

const Instruction *Instructions::ICACHE_FILL_WITH_LOCK = new InstructionAnonymousInnerClass6();

	Instructions::InstructionAnonymousInnerClass6::InstructionAnonymousInnerClass6() : Instruction(5)
	{
	}

	string Instructions::InstructionAnonymousInnerClass6::name()
	{
		return "CACHE 0x0B";
	}

	string Instructions::InstructionAnonymousInnerClass6::category()
	{
		return "ALLEGREX";
	}

	void Instructions::InstructionAnonymousInnerClass6::interpret(Processor *processor, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;


	}

	void Instructions::InstructionAnonymousInnerClass6::compile(Processor *processor, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;


	}

	string Instructions::InstructionAnonymousInnerClass6::disasm(int address, int insn)
	{
		int imm16 = (insn >> 0) & 65535;
		int rs = (insn >> 21) & 31;

	return Common::disasmCODEIMMRS("cache", 0x0B, DisHelper::signExtend(imm16), rs);
	}

const Instruction *Instructions::DCACHE_INDEX_WRITEBACK_INVALIDATE = new InstructionAnonymousInnerClass7();

	Instructions::InstructionAnonymousInnerClass7::InstructionAnonymousInnerClass7() : Instruction(6)
	{
	}

	string Instructions::InstructionAnonymousInnerClass7::name()
	{
		return "CACHE 0x14";
	}

	string Instructions::InstructionAnonymousInnerClass7::category()
	{
		return "ALLEGREX";
	}

	void Instructions::InstructionAnonymousInnerClass7::interpret(Processor *processor, int insn)
	{

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
