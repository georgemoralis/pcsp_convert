using namespace std;

#include "HiLoState.h"

namespace jpcsp::Allegrex
{

	void HiLoState::setHi(int value)
	{
		hilo = (hilo & 0xffffffffLL) | (static_cast<long long>(value) << 32);
	}

	int HiLoState::getHi()
	{
		return static_cast<int>(static_cast<long long>(static_cast<unsigned long long>(hilo) >> 32));
	}

	void HiLoState::setLo(int value)
	{
		hilo = (hilo & ~0xffffffffLL) | ((static_cast<long long>(value)) & 0xffffffffLL);
	}

	int HiLoState::getLo()
	{
		return static_cast<int>(hilo & 0xffffffffLL);
	}

	void HiLoState::reset()
	{
		GprState::reset();
		hilo = 0;
	}

	HiLoState::HiLoState()
	{
		reset();
	}

	void HiLoState::copy(HiLoState *that)
	{
		GprState::copy(that);
		hilo = that->hilo;
	}

	HiLoState::HiLoState(const HiLoState &that)
	{
		copy(that);
	}
}
