#pragma once

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
	class GprState
	{
	public:
		int *gpr;

		virtual ~GprState()
		{
			delete[] gpr;
		}

		virtual void reset();

		GprState();

		virtual void copy(GprState *that);

		GprState(const GprState &that);
	};

}
