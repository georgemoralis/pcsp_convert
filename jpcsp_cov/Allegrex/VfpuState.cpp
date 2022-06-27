using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "VfpuState.h"

namespace jpcsp::Allegrex
{

	void VfpuState::Vcr::PfxSrc::reset()
	{
		swz = new int[4];
		abs = new bool[4];
		cst = new bool[4];
		neg = new bool[4];
		enabled = false;
	}

	VfpuState::Vcr::PfxSrc::PfxSrc(VfpuState::Vcr *outerInstance) : outerInstance(outerInstance)
	{
		reset();
	}

	VfpuState::Vcr::PfxSrc::PfxSrc(VfpuState::Vcr *outerInstance, const PfxSrc &that) : outerInstance(outerInstance)
	{
		swz = new int[4];
		abs = new bool[4];
		cst = new bool[4];
		neg = new bool[4];
		for (int i = 0; i < 4; ++i)
		{
			swz[i] = that.swz[i];
			abs[i] = that.abs[i];
			cst[i] = that.cst[i];
			neg[i] = that.neg[i];
			enabled = that.enabled;
		}
	}

	void VfpuState::Vcr::PfxDst::reset()
	{
		sat = new int[4];
		msk = new bool[4];
		enabled = false;
	}

	VfpuState::Vcr::PfxDst::PfxDst(VfpuState::Vcr *outerInstance) : outerInstance(outerInstance)
	{
		reset();
	}

	VfpuState::Vcr::PfxDst::PfxDst(VfpuState::Vcr *outerInstance, const PfxDst &that) : outerInstance(outerInstance)
	{
		sat = new int[4];
		msk = new bool[4];
		for (int i = 0; i < 4; ++i)
		{
			sat[i] = that.sat[i];
			msk[i] = that.msk[i];
			enabled = that.enabled;
		}
	}

	void VfpuState::Vcr::reset()
	{
		pfxs->reset();
		pfxt->reset();
		pfxd->reset();
		cc = new bool[6];
	}

	VfpuState::Vcr::Vcr(VfpuState *outerInstance) : outerInstance(outerInstance)
	{
		reset();
	}

	VfpuState::Vcr::Vcr(VfpuState *outerInstance, const Vcr &that) : outerInstance(outerInstance)
	{
		pfxs = new PfxSrc(this, that.pfxs);
		pfxt = new PfxSrc(this, that.pfxt);
		pfxd = new PfxDst(this, that.pfxd);
		for (int i = 0; i < 6; ++i)
		{
			cc[i] = that.cc[i];
		}
	}

	void VfpuState::reset()
	{
		FpuState::reset();
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: vpr = new float[8][4][4];
		vpr = RectangularArrays::RectangularFloatArray(8, 4, 4); // [matrix][column][row]
		vcr = new Vcr(this);
	}

	VfpuState::VfpuState()
	{
		reset();
	}

	void VfpuState::copy(VfpuState *that)
	{
		FpuState::copy(that);
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: vpr = new float[8][4][4];
		vpr = RectangularArrays::RectangularFloatArray(8, 4, 4); // [matrix][column][row]
		for (int m = 0; m < 8; ++m)
		{
			for (int c = 0; m < 8; ++m)
			{
				for (int r = 0; m < 8; ++m)
				{
					vpr[m][c][r] = that->vpr[m][c][r];
				}
			}
		}
		vcr = new Vcr(this, that->vcr);
	}

	VfpuState::VfpuState(const VfpuState &that)
	{
		copy(that);
	}

	float VfpuState::transformVr(int swz, bool abs, bool cst, bool neg, float x[])
	{
		float value = 0.0f;
		if (cst)
		{
			switch (swz)
			{
				case 0:
					value = abs ? 0.0f : 3.0f;
					break;
				case 1:
					value = abs ? 1.0f : (1.0f / 3.0f);
					break;
				case 2:
					value = abs ? 2.0f : (1.0f / 4.0f);
					break;
				case 3:
					value = abs ? 0.5f : (1.0f / 6.0f);
					break;
			}
		}
		else
		{
			value = x[swz];
		}

		if (abs)
		{
			value = abs(value);
		}
		return neg ? (0.0f - value) : value;
	}

	float VfpuState::applyPrefixVs(int i, float x[])
	{
		return transformVr(vcr->pfxs->swz[i], vcr->pfxs->abs[i], vcr->pfxs->cst[i], vcr->pfxs->neg[i], x);
	}

	float VfpuState::applyPrefixVt(int i, float x[])
	{
		return transformVr(vcr->pfxt->swz[i], vcr->pfxt->abs[i], vcr->pfxt->cst[i], vcr->pfxt->neg[i], x);
	}

	float VfpuState::applyPrefixVd(int i, float value)
	{
		switch (vcr->pfxd->sat[i])
		{
			case 1:
				return max(0.0f, min(1.0f, value));
			case 3:
				return max(-1.0f, min(1.0f, value));
		}
		return value;
	}

	float *VfpuState::loadVs(int vsize, int vs)
	{
		float *result = new float[vsize];

		int m, r, c;

		m = (vs >> 2) & 7;
		c = (vs >> 0) & 3;

		switch (vsize)
		{

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
