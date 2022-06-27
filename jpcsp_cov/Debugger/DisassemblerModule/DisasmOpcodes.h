#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "../../AllegrexInstructions.h"
#include "../../AllegrexDecoder.h"
#include <string>

/*
This file is part of jpcsp.

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
namespace jpcsp::Debugger::DisassemblerModule
{

	using namespace jpcsp::Debugger::DisassemblerModule;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.Debugger.DisassemblerModule.DisHelper.*;
	using AllegrexInstructions = jpcsp::AllegrexInstructions;
	using AllegrexDecoder = jpcsp::AllegrexDecoder;

	/**
	 *
	 * @author shadow
	 */
	class DisasmOpcodes : public AllegrexInstructions
	{

	private:
//JAVA TO C++ CONVERTER NOTE: Field name conflicts with a method name of the current type:
		AllegrexDecoder *const disasm = new AllegrexDecoder();
	public:
		int opcode_address = 0;
		std::string returnString = "Unsupported Instruction"; // set default to unsupported

		virtual ~DisasmOpcodes()
		{
			delete disasm_Conflict;
		}

		virtual std::string disasm(int value, int opcode_address);

		void doUNK(const std::string &reason) override;

		void doNOP() override;

		void doSLL(int rd, int rt, int sa) override;

		void doSRL(int rd, int rt, int sa) override;

		void doSRA(int rd, int rt, int sa) override;

		void doSLLV(int rd, int rt, int rs) override;

		void doSRLV(int rd, int rt, int rs) override;

		void doSRAV(int rd, int rt, int rs) override;

		void doJR(int rs) override;

		void doJALR(int rd, int rs) override;

		void doMFHI(int rd) override;

		void doMTHI(int rs) override;

		void doMFLO(int rd) override;

		void doMTLO(int rs) override;

		void doMULT(int rs, int rt) override;

		void doMULTU(int rs, int rt) override;

		void doDIV(int rs, int rt) override;

		void doDIVU(int rs, int rt) override;

		void doADD(int rd, int rs, int rt) override;

		void doADDU(int rd, int rs, int rt) override;

		void doSUB(int rd, int rs, int rt) override;

		void doSUBU(int rd, int rs, int rt) override;

		void doAND(int rd, int rs, int rt) override;

		void doOR(int rd, int rs, int rt) override;

		void doXOR(int rd, int rs, int rt) override;

		void doNOR(int rd, int rs, int rt) override;

		void doSLT(int rd, int rs, int rt) override;

		void doSLTU(int rd, int rs, int rt) override;

		void doBLTZ(int rs, int simm16) override;

		void doBGEZ(int rs, int simm16) override;

		void doBLTZL(int rs, int simm16) override;

		void doBGEZL(int rs, int simm16) override;

		void doBLTZAL(int rs, int simm16) override;

		void doBGEZAL(int rs, int simm16) override;

		void doBLTZALL(int rs, int simm16) override;

		void doBGEZALL(int rs, int simm16) override;

		void doJ(int uimm26) override;

		void doJAL(int uimm26) override;

		void doBEQ(int rs, int rt, int simm16) override;

		void doBNE(int rs, int rt, int simm16) override;

		void doBLEZ(int rs, int simm16) override;

		void doBGTZ(int rs, int simm16) override;

		void doBEQL(int rs, int rt, int simm16) override;

		void doBNEL(int rs, int rt, int simm16) override;

		void doBLEZL(int rs, int simm16) override;

		void doBGTZL(int rs, int simm16) override;

		void doADDI(int rt, int rs, int simm16) override;

		void doADDIU(int rt, int rs, int simm16) override;

		void doSLTI(int rt, int rs, int simm16) override;

		void doSLTIU(int rt, int rs, int simm16) override;

		void doANDI(int rt, int rs, int uimm16) override;

		void doORI(int rt, int rs, int uimm16) override;

		void doXORI(int rt, int rs, int uimm16) override;

		void doLUI(int rt, int uimm16) override;

		void doHALT() override;

		void doMFIC(int rt) override;

		void doMTIC(int rt) override;

		void doMFC0(int rt, int c0dr) override;

		void doCFC0(int rt, int c0cr) override;

		void doMTC0(int rt, int c0dr) override;

		void doCTC0(int rt, int c0cr) override;

		void doERET() override;

		void doLB(int rt, int rs, int simm16) override;

		void doLBU(int rt, int rs, int simm16) override;

		void doLH(int rt, int rs, int simm16) override;

		void doLHU(int rt, int rs, int simm16) override;

		void doLWL(int rt, int rs, int simm16) override;

		void doLW(int rt, int rs, int simm16) override;

		void doLWR(int rt, int rs, int simm16) override;

		void doSB(int rt, int rs, int simm16) override;

		void doSH(int rt, int rs, int simm16) override;

		void doSWL(int rt, int rs, int simm16) override;

		void doSW(int rt, int rs, int simm16) override;

		void doSWR(int rt, int rs, int simm16) override;

		void doCACHE(int rt, int rs, int simm16) override;

		void doLL(int rt, int rs, int simm16) override;

		void doLWC1(int ft, int rs, int simm16) override;

		void doLVS(int vt, int rs, int simm14) override;

		void doSC(int rt, int rs, int simm16) override;

		void doSWC1(int ft, int rs, int simm16) override;

		void doSVS(int vt, int rs, int simm14) override;

		void doROTR(int rd, int rt, int sa) override;

		void doROTRV(int rd, int rt, int rs) override;

		void doMOVZ(int rd, int rs, int rt) override;

		void doMOVN(int rd, int rs, int rt) override;

		void doSYSCALL(int code) override;

		void doBREAK(int code) override;


//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
