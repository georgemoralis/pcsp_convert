using namespace std;

#include "GprState.h"

namespace jpcsp::Allegrex
{

	void GprState::reset()
	{
		gpr = new int[32];
	}

	GprState::GprState()
	{
		reset();
	}

	void GprState::copy(GprState *that)
	{
		gpr = new int[32];
		for (int reg = 0; reg < 32; ++reg)
		{
			gpr[reg] = that->gpr[reg];
		}
	}

	GprState::GprState(const GprState &that)
	{
		this->copy(that);
	}
}
