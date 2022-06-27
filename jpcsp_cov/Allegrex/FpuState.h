#pragma once

#include "HiLoState.h"

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
	class FpuState : public HiLoState
	{

	public:
		class Fcr0 final
		{

		public:
			static constexpr int imp = 0; // FPU design number

			static constexpr int rev = 0; // FPU revision bumber

		};

	public:
		class Fcr31
		{
		private:
			FpuState *outerInstance;


		public:
			int rm = 0;
			bool c = false;
			bool fs = false;

			virtual ~Fcr31()
			{
				delete outerInstance;
			}

			virtual void reset();

			Fcr31(FpuState *outerInstance);

			Fcr31(FpuState *outerInstance, const Fcr31 &that);
		};
	public:
		float *fpr;
		Fcr31 *fcr31;

		virtual ~FpuState()
		{
			delete[] fpr;
			delete fcr31;
		}

		void reset() override;

		FpuState();

		virtual void copy(FpuState *that);

		FpuState(const FpuState &that);
	};

}
