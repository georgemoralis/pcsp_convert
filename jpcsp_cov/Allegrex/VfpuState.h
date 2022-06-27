#pragma once

#include "FpuState.h"
#include <cmath>
#include "../RectangularArrays.h"

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
	class VfpuState : public FpuState
	{

	public:
		float ***vpr;

	public:
		class Vcr
		{
		private:
			VfpuState *outerInstance;


		public:
			class PfxSrc
			{
			private:
				VfpuState::Vcr *outerInstance;


			public:
				int *swz;
				bool *abs;
				bool *cst;
				bool *neg;
				bool enabled = false;

				virtual ~PfxSrc()
				{
					delete[] swz;
					delete[] abs;
					delete[] cst;
					delete[] neg;
					delete outerInstance;
				}

				virtual void reset();

				PfxSrc(VfpuState::Vcr *outerInstance);

				PfxSrc(VfpuState::Vcr *outerInstance, const PfxSrc &that);
			};
		public:
			PfxSrc *pfxs;
			PfxSrc *pfxt;

		public:
			class PfxDst
			{
			private:
				VfpuState::Vcr *outerInstance;


			public:
				int *sat;
				bool *msk;
				bool enabled = false;

				virtual ~PfxDst()
				{
					delete[] sat;
					delete[] msk;
					delete outerInstance;
				}

				virtual void reset();

				PfxDst(VfpuState::Vcr *outerInstance);

				PfxDst(VfpuState::Vcr *outerInstance, const PfxDst &that);
			};
		public:
			PfxDst *pfxd;
			bool *cc;

			virtual ~Vcr()
			{
				delete pfxs;
				delete pfxt;
				delete pfxd;
				delete[] cc;
				delete outerInstance;
			}

			virtual void reset();

			Vcr(VfpuState *outerInstance);

			Vcr(VfpuState *outerInstance, const Vcr &that);
		};
	public:
		Vcr *vcr;

		virtual ~VfpuState()
		{
			delete[] vpr;
			delete vcr;
		}

		void reset() override;

		VfpuState();

		virtual void copy(VfpuState *that);

		VfpuState(const VfpuState &that);

		// VFPU stuff
	private:
		float transformVr(int swz, bool abs, bool cst, bool neg, float x[]);

		float applyPrefixVs(int i, float x[]);

		float applyPrefixVt(int i, float x[]);

		float applyPrefixVd(int i, float value);

	public:
		virtual float *loadVs(int vsize, int vs);

		virtual float *loadVt(int vsize, int vt);

		virtual void saveVd(int vsize, int vd, float result[]);

	};

}
