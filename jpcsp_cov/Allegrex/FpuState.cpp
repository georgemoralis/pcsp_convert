using namespace std;

#include "FpuState.h"

namespace jpcsp::Allegrex
{

	void FpuState::Fcr31::reset()
	{
		rm = 0;
		c = false;
		fs = false;
	}

	FpuState::Fcr31::Fcr31(FpuState *outerInstance) : outerInstance(outerInstance)
	{
		reset();
	}

	FpuState::Fcr31::Fcr31(FpuState *outerInstance, const Fcr31 &that) : outerInstance(outerInstance)
	{
		rm = that.rm;
		c = that.c;
		fs = that.fs;
	}

	void FpuState::reset()
	{
		HiLoState::reset();
		fpr = new float[32];
		fcr31 = new Fcr31(this);
	}

	FpuState::FpuState()
	{
		reset();
	}

	void FpuState::copy(FpuState *that)
	{
		HiLoState::copy(that);
		fpr = new float[32];
		for (int reg = 0; reg < 32; ++reg)
		{
			fpr[reg] = that->fpr[reg];
		}
		fcr31 = new Fcr31(this, that->fcr31);
	}

	FpuState::FpuState(const FpuState &that)
	{
		copy(that);
	}
}
