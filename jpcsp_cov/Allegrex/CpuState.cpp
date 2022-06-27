using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "CpuState.h"

namespace jpcsp::Allegrex
{

	void CpuState::reset()
	{
		VfpuState::reset();
	}

	CpuState::CpuState()
	{
		reset();
	}

	void CpuState::copy(CpuState *that)
	{
		VfpuState::copy(that);
	}

	CpuState::CpuState(const CpuState &that)
	{
		copy(that);
	}

	long long CpuState::signedDivMod(int x, int y)
	{
		return (static_cast<long long>(x % y)) << 32 | ((static_cast<long long>(x / y)) & 0xffffffff);
	}

	long long CpuState::unsignedDivMod(long long x, long long y)
	{
		return ((x % y)) << 32 | ((x / y) & 0xffffffff);
	}

	int CpuState::max(int x, int y)
	{
		return (x > y) ? x : y;
	}

	int CpuState::min(int x, int y)
	{
		return (x < y) ? x : y;
	}

	int CpuState::extractBits(int x, int pos, int len)
	{
		return (static_cast<int>(static_cast<unsigned int>(x) >> pos)) & ~(~0 << len);
	}

	int CpuState::insertBits(int x, int y, int lsb, int msb)
	{
		int mask = ~(~0 << (msb - lsb + 1)) << lsb;
		return (x & ~mask) | ((y << lsb) & mask);
	}

	int CpuState::signExtend(int value)
	{
		return (value << 16) >> 16;
	}

	int CpuState::signExtend8(int value)
	{
		return (value << 24) >> 24;
	}

	int CpuState::zeroExtend(int value)
	{
		return (value & 0xffff);
	}

	int CpuState::zeroExtend8(int value)
	{
		return (value & 0xff);
	}

	int CpuState::signedCompare(int i, int j)
	{
		return static_cast<int>(static_cast<unsigned int>((i - j)) >> 31);
	}

	int CpuState::unsignedCompare(int i, int j)
	{
		return static_cast<int>(static_cast<unsigned int>(((i - j) ^ i ^ j)) >> 31);
	}

	int CpuState::branchTarget(int npc, int simm16)
	{
		return npc + (simm16 << 2);
	}

	int CpuState::jumpTarget(int npc, int uimm26)
	{
		return (npc & 0xf0000000) | (uimm26 << 2);
	}

	void CpuState::doSLL(int rd, int rt, int sa)
	{
		if (rd != 0)
		{
			gpr[rd] = (gpr[rt] << sa);
		}
	}

	void CpuState::doSRL(int rd, int rt, int sa)
	{
		if (rd != 0)
		{
			gpr[rd] = (static_cast<int>(static_cast<unsigned int>(gpr[rt]) >> sa));
		}
	}

	void CpuState::doSRA(int rd, int rt, int sa)
	{
		if (rd != 0)
		{
			gpr[rd] = (gpr[rt] >> sa);
		}
	}

	void CpuState::doSLLV(int rd, int rt, int rs)
	{
		if (rd != 0)
		{
				gpr[rd] = (gpr[rt] << (gpr[rs] & 31));
		}
	}

	void CpuState::doSRLV(int rd, int rt, int rs)
	{
		if (rd != 0)
		{
				gpr[rd] = (static_cast<int>(static_cast<unsigned int>(gpr[rt]) >> (gpr[rs] & 31)));
		}
	}

	void CpuState::doSRAV(int rd, int rt, int rs)
	{
		if (rd != 0)
		{
				gpr[rd] = (gpr[rt] >> (gpr[rs] & 31));
		}
	}

	void CpuState::doMFHI(int rd)
	{
		if (rd != 0)
		{
			gpr[rd] = getHi();
		}
	}

	void CpuState::doMTHI(int rs)
	{
		int hi = gpr[rs];
		hilo = ((static_cast<long long>(hi)) << 32) | (hilo & 0xffffffff);
	}

	void CpuState::doMFLO(int rd)
	{
		if (rd != 0)
		{
			gpr[rd] = getLo();
		}
	}

	void CpuState::doMTLO(int rs)
	{
		int lo = gpr[rs];
		hilo = (hilo & 0xffffffff00000000LL) | ((static_cast<long long>(lo)) & 0x00000000ffffffffLL);
	}

	void CpuState::doMULT(int rs, int rt)
	{
		hilo = (static_cast<long long>(gpr[rs])) * (static_cast<long long>(gpr[rt]));
	}

	void CpuState::doMULTU(int rs, int rt)
	{
		hilo = ((static_cast<long long>(gpr[rs])) & 0xffffffff) * ((static_cast<long long>(gpr[rt])) & 0xffffffff);
	}

	void CpuState::doDIV(int rs, int rt)
	{
		int lo = gpr[rs] / gpr[rt];
		int hi = gpr[rs] % gpr[rt];
		hilo = (static_cast<long long>(hi)) << 32 | ((static_cast<long long>(lo)) & 0xffffffff);
	}

	void CpuState::doDIVU(int rs, int rt)
	{
		long long x = (static_cast<long long>(gpr[rs])) & 0xffffffff;
		long long y = (static_cast<long long>(gpr[rt])) & 0xffffffff;
		int lo = static_cast<int>(x / y);
		int hi = static_cast<int>(x % y);
		hilo = (static_cast<long long>(hi)) << 32 | ((static_cast<long long>(lo)) & 0xffffffff);
	}

	void CpuState::doADDU(int rd, int rs, int rt)
	{
		if (rd != 0)
		{
			gpr[rd] = gpr[rs] + gpr[rt];
		}
	}

	void CpuState::doSUBU(int rd, int rs, int rt)
	{
		if (rd != 0)
		{
			gpr[rd] = gpr[rs] - gpr[rt];
		}
	}

	void CpuState::doAND(int rd, int rs, int rt)
	{
		if (rd != 0)
		{
			gpr[rd] = gpr[rs] & gpr[rt];
		}
	}

	void CpuState::doOR(int rd, int rs, int rt)
	{
		if (rd != 0)
		{
			gpr[rd] = gpr[rs] | gpr[rt];
		}
	}

	void CpuState::doXOR(int rd, int rs, int rt)
	{
		if (rd != 0)
		{
			gpr[rd] = gpr[rs] ^ gpr[rt];
		}
	}

	void CpuState::doNOR(int rd, int rs, int rt)
	{
		if (rd != 0)
		{
			gpr[rd] = ~(gpr[rs] | gpr[rt]);
		}
	}


//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
