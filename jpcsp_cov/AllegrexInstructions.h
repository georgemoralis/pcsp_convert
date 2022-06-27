#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

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
namespace jpcsp
{

	/**
	 *
	 * @author hli
	 */
	class AllegrexInstructions
	{

	public:
		virtual void doUNK(const std::string &reason) = 0;

		virtual void doNOP() = 0;

		virtual void doSLL(int rd, int rt, int sa) = 0;

		virtual void doSRL(int rd, int rt, int sa) = 0;

		virtual void doSRA(int rd, int rt, int sa) = 0;

		virtual void doSLLV(int rd, int rt, int rs) = 0;

		virtual void doSRLV(int rd, int rt, int rs) = 0;

		virtual void doSRAV(int rd, int rt, int rs) = 0;

		virtual void doJR(int rs) = 0;

		virtual void doJALR(int rd, int rs) = 0;

		virtual void doMFHI(int rd) = 0;

		virtual void doMTHI(int rs) = 0;

		virtual void doMFLO(int rd) = 0;

		virtual void doMTLO(int rs) = 0;

		virtual void doMULT(int rs, int rt) = 0;

		virtual void doMULTU(int rs, int rt) = 0;

		virtual void doDIV(int rs, int rt) = 0;

		virtual void doDIVU(int rs, int rt) = 0;

		virtual void doADD(int rd, int rs, int rt) = 0;

		virtual void doADDU(int rd, int rs, int rt) = 0;

		virtual void doSUB(int rd, int rs, int rt) = 0;

		virtual void doSUBU(int rd, int rs, int rt) = 0;

		virtual void doAND(int rd, int rs, int rt) = 0;

		virtual void doOR(int rd, int rs, int rt) = 0;

		virtual void doXOR(int rd, int rs, int rt) = 0;

		virtual void doNOR(int rd, int rs, int rt) = 0;

		virtual void doSLT(int rd, int rs, int rt) = 0;

		virtual void doSLTU(int rd, int rs, int rt) = 0;

		virtual void doBLTZ(int rs, int simm16) = 0;

		virtual void doBGEZ(int rs, int simm16) = 0;

		virtual void doBLTZL(int rs, int simm16) = 0;

		virtual void doBGEZL(int rs, int simm16) = 0;

		virtual void doBLTZAL(int rs, int simm16) = 0;

		virtual void doBGEZAL(int rs, int simm16) = 0;

		virtual void doBLTZALL(int rs, int simm16) = 0;

		virtual void doBGEZALL(int rs, int simm16) = 0;

		virtual void doJ(int uimm26) = 0;

		virtual void doJAL(int uimm26) = 0;

		virtual void doBEQ(int rs, int rt, int simm16) = 0;

		virtual void doBNE(int rs, int rt, int simm16) = 0;

		virtual void doBLEZ(int rs, int simm16) = 0;

		virtual void doBGTZ(int rs, int simm16) = 0;

		virtual void doBEQL(int rs, int rt, int simm16) = 0;

		virtual void doBNEL(int rs, int rt, int simm16) = 0;

		virtual void doBLEZL(int rs, int simm16) = 0;

		virtual void doBGTZL(int rs, int simm16) = 0;

		virtual void doADDI(int rt, int rs, int simm16) = 0;

		virtual void doADDIU(int rt, int rs, int simm16) = 0;

		virtual void doSLTI(int rt, int rs, int simm16) = 0;

		virtual void doSLTIU(int rt, int rs, int simm16) = 0;

		virtual void doANDI(int rt, int rs, int uimm16) = 0;

		virtual void doORI(int rt, int rs, int uimm16) = 0;

		virtual void doXORI(int rt, int rs, int uimm16) = 0;

		virtual void doLUI(int rt, int uimm16) = 0;

		virtual void doHALT() = 0;

		virtual void doMFIC(int rt) = 0;

		virtual void doMTIC(int rt) = 0;

		virtual void doMFC0(int rt, int c0dr) = 0;

		virtual void doCFC0(int rt, int c0cr) = 0;

		virtual void doMTC0(int rt, int c0dr) = 0;

		virtual void doCTC0(int rt, int c0cr) = 0;

		virtual void doERET() = 0;

		virtual void doLB(int rt, int rs, int simm16) = 0;

		virtual void doLBU(int rt, int rs, int simm16) = 0;

		virtual void doLH(int rt, int rs, int simm16) = 0;

		virtual void doLHU(int rt, int rs, int simm16) = 0;

		virtual void doLWL(int rt, int rs, int simm16) = 0;

		virtual void doLW(int rt, int rs, int simm16) = 0;

		virtual void doLWR(int rt, int rs, int simm16) = 0;

		virtual void doSB(int rt, int rs, int simm16) = 0;

		virtual void doSH(int rt, int rs, int simm16) = 0;

		virtual void doSWL(int rt, int rs, int simm16) = 0;

		virtual void doSW(int rt, int rs, int simm16) = 0;

		virtual void doSWR(int rt, int rs, int simm16) = 0;

		virtual void doCACHE(int rt, int rs, int simm16) = 0;

		virtual void doLL(int rt, int rs, int simm16) = 0;

		virtual void doLWC1(int rt, int rs, int simm16) = 0;

		virtual void doLVS(int vt, int rs, int simm14) = 0;

		virtual void doSC(int rt, int rs, int simm16) = 0;

		virtual void doSWC1(int rt, int rs, int simm16) = 0;

		virtual void doSVS(int vt, int rs, int simm14) = 0;

		virtual void doROTR(int rd, int rt, int sa) = 0;

		virtual void doROTRV(int rd, int rt, int rs) = 0;

		virtual void doMOVZ(int rd, int rs, int rt) = 0;

		virtual void doMOVN(int rd, int rs, int rt) = 0;

		virtual void doSYSCALL(int code) = 0;

		virtual void doBREAK(int code) = 0;

		virtual void doSYNC() = 0;

		virtual void doCLZ(int rd, int rs) = 0;

		virtual void doCLO(int rd, int rs) = 0;

		virtual void doMADD(int rs, int rt) = 0;

		virtual void doMADDU(int rs, int rt) = 0;

		virtual void doMAX(int rd, int rs, int rt) = 0;

		virtual void doMIN(int rd, int rs, int rt) = 0;

		virtual void doMSUB(int rs, int rt) = 0;

		virtual void doMSUBU(int rs, int rt) = 0;

		virtual void doEXT(int rt, int rs, int rd, int sa) = 0;


//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
