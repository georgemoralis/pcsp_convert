#pragma once

#include "GprState.h"

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
	class HiLoState : public GprState
	{

	public:
		long long hilo = 0;

		virtual void setHi(int value);

		virtual int getHi();

		virtual void setLo(int value);

		virtual int getLo();

		void reset() override;

		HiLoState();

		virtual void copy(HiLoState *that);

		HiLoState(const HiLoState &that);
	};

}
