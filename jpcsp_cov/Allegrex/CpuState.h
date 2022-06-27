#pragma once

#include "VfpuState.h"

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
namespace jpcsp::Allegrex
{

	/**
	 *
	 * @author hli
	 */

	class CpuState : public VfpuState
	{

	public:
		void reset() override;

		CpuState();

		virtual void copy(CpuState *that);

		CpuState(const CpuState &that);

		static long long signedDivMod(int x, int y) final;

		static long long unsignedDivMod(long long x, long long y) final;

		static int max(int x, int y) final;

		static int min(int x, int y) final;

		static int extractBits(int x, int pos, int len) final;

		static int insertBits(int x, int y, int lsb, int msb) final;

		static int signExtend(int value) final;

		static int signExtend8(int value) final;

		static int zeroExtend(int value) final;

		static int zeroExtend8(int value) final;

		static int signedCompare(int i, int j) final;

		static int unsignedCompare(int i, int j) final;

		static int branchTarget(int npc, int simm16) final;

		static int jumpTarget(int npc, int uimm26) final;

		void doSLL(int rd, int rt, int sa);

		void doSRL(int rd, int rt, int sa);

		void doSRA(int rd, int rt, int sa);

		void doSLLV(int rd, int rt, int rs);

		void doSRLV(int rd, int rt, int rs);

		void doSRAV(int rd, int rt, int rs);

		void doMFHI(int rd);

		void doMTHI(int rs);

		void doMFLO(int rd);

		void doMTLO(int rs);

		void doMULT(int rs, int rt);

		void doMULTU(int rs, int rt);

		void doDIV(int rs, int rt);

		void doDIVU(int rs, int rt);

		void doADDU(int rd, int rs, int rt);

		void doSUBU(int rd, int rs, int rt);

		void doAND(int rd, int rs, int rt);

		void doOR(int rd, int rs, int rt);

		void doXOR(int rd, int rs, int rt);

		void doNOR(int rd, int rs, int rt);

		void doSLT(int rd, int rs, int rt);

		void doSLTU(int rd, int rs, int rt);


		void doADDIU(int rt, int rs, int simm16);

		void doSLTI(int rt, int rs, int simm16);

		void doSLTIU(int rt, int rs, int simm16);

		void doANDI(int rt, int rs, int uimm16);

		void doORI(int rt, int rs, int uimm16);

		void doXORI(int rt, int rs, int uimm16);

		void doLUI(int rt, int uimm16);

		void doROTR(int rd, int rt, int sa);

		void doROTRV(int rd, int rt, int rs);

		void doMOVZ(int rd, int rs, int rt);

		void doMOVN(int rd, int rs, int rt);

		void doCLZ(int rd, int rs);

		void doCLO(int rd, int rs);

		void doMADD(int rs, int rt);

		void doMADDU(int rs, int rt);

		void doMAX(int rd, int rs, int rt);

		void doMIN(int rd, int rs, int rt);

		void doMSUB(int rs, int rt);

		void doMSUBU(int rs, int rt);

		void doEXT(int rt, int rs, int rd, int sa);

		void doINS(int rt, int rs, int rd, int sa);

		void doWSBH(int rd, int rt);

		void doWSBW(int rd, int rt);

		void doSEB(int rd, int rt);

		void doBITREV(int rd, int rt);

		void doSEH(int rd, int rt);
	};

}
