#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#define _USE_MATH_DEFINES
#include "../Processor.h"
#include "Common.h"
#include <string>
#include <cmath>
#include "../bankersrounding.h"

/* this is an auto-generated file from Allegrex.isa file */
/* This file is part of jpcsp.
Jpcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Jpcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Jpcsp.  If not, see <http://www.gnu.org/licenses/>.
 */

namespace jpcsp::Allegrex
{



	using namespace jpcsp::Debugger::DisassemblerModule;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.Debugger.DisassemblerModule.DisHelper.*;

	/**
	 *
	 * @author hli
	 */
	class Instructions
	{


public:
	static const jpcsp::Allegrex::Common::Instruction *NOP;

private:
	class InstructionAnonymousInnerClass : public Instruction
	{
	public:
		InstructionAnonymousInnerClass();


	std::string name() final override;
	std::string category() final override;
	void interpret(Processor *processor, int insn) override;
	void compile(Processor *processor, int insn) override;
	std::string disasm(int address, int insn) override;
	};
public:
	static const jpcsp::Allegrex::Common::Instruction *ICACHE_INDEX_INVALIDATE;

private:
	class InstructionAnonymousInnerClass2 : public Instruction
	{
	public:
		InstructionAnonymousInnerClass2();


	std::string name() final override;
	std::string category() final override;
	void interpret(Processor *processor, int insn) override;
	void compile(Processor *processor, int insn) override;
	std::string disasm(int address, int insn) override;
	};
public:
	static const jpcsp::Allegrex::Common::Instruction *ICACHE_INDEX_UNLOCK;

private:
	class InstructionAnonymousInnerClass3 : public Instruction
	{
	public:
		InstructionAnonymousInnerClass3();


	std::string name() final override;
	std::string category() final override;
	void interpret(Processor *processor, int insn) override;
	void compile(Processor *processor, int insn) override;
	std::string disasm(int address, int insn) override;
	};
public:
	static const jpcsp::Allegrex::Common::Instruction *ICACHE_HIT_INVALIDATE;

private:
	class InstructionAnonymousInnerClass4 : public Instruction
	{
	public:
		InstructionAnonymousInnerClass4();


	std::string name() final override;
	std::string category() final override;
	void interpret(Processor *processor, int insn) override;
	void compile(Processor *processor, int insn) override;
	std::string disasm(int address, int insn) override;
	};
public:
	static const jpcsp::Allegrex::Common::Instruction *ICACHE_FILL;

private:
	class InstructionAnonymousInnerClass5 : public Instruction
	{
	public:
		InstructionAnonymousInnerClass5();


	std::string name() final override;
	std::string category() final override;
	void interpret(Processor *processor, int insn) override;
	void compile(Processor *processor, int insn) override;
	std::string disasm(int address, int insn) override;
	};
public:
	static const jpcsp::Allegrex::Common::Instruction *ICACHE_FILL_WITH_LOCK;

private:
	class InstructionAnonymousInnerClass6 : public Instruction
	{
	public:
		InstructionAnonymousInnerClass6();


	std::string name() final override;
	std::string category() final override;
	void interpret(Processor *processor, int insn) override;
	void compile(Processor *processor, int insn) override;
	std::string disasm(int address, int insn) override;
	};
public:
	static const jpcsp::Allegrex::Common::Instruction *DCACHE_INDEX_WRITEBACK_INVALIDATE;

private:
	class InstructionAnonymousInnerClass7 : public Instruction
	{
	public:
		InstructionAnonymousInnerClass7();


	std::string name() final override;
	std::string category() final override;
	void interpret(Processor *processor, int insn) override;
	void compile(Processor *processor, int insn) override;
	std::string disasm(int address, int insn) override;
	};
public:
	static const jpcsp::Allegrex::Common::Instruction *DCACHE_INDEX_UNLOCK;

private:
	class InstructionAnonymousInnerClass8 : public Instruction
	{
	public:
		InstructionAnonymousInnerClass8();


	std::string name() final override;
	std::string category() final override;
	void interpret(Processor *processor, int insn) override;
	void compile(Processor *processor, int insn) override;
	std::string disasm(int address, int insn) override;
	};
public:

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
