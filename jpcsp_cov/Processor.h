#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "HLE/SyscallHandler.h"
#include "AllegrexInstructions.h"
#include "Allegrex/CpuState.h"
#include "AllegrexBasicBlock.h"
#include "AllegrexDecoder.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <cmath>
#include <cassert>
#include "RectangularArrays.h"
#include "bankersrounding.h"

/*
This file is part of jpcsp.

Jpcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Jpcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Jpcsp.  If not, see <http://www.gnu.org/licenses/>.
 */
namespace jpcsp
{

	//import static jpcsp.AllegrexInstructions;
	using namespace jpcsp::Allegrex;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;

	class Processor : public AllegrexInstructions
	{

	public:
		CpuState *cpu;

		static constexpr int fcr0_imp = 0; // FPU design number

		static constexpr int fcr0_rev = 0; // FPU revision bumber

		int *gpr;
		float *fpr;
		float ***vpr;
		long long hilo = 0;
		int pc = 0, npc = 0;
		int fcr31_rm = 0;
		bool fcr31_c = false;
		bool fcr31_fs = false;
		bool *vcr_cc;
		int *vcr_pfxs_swz;
		bool *vcr_pfxs_abs;
		bool *vcr_pfxs_cst;
		bool *vcr_pfxs_neg;
		bool vcr_pfxs = false;
		int *vcr_pfxt_swz;
		bool *vcr_pfxt_abs;
		bool *vcr_pfxt_cst;
		bool *vcr_pfxt_neg;
		bool vcr_pfxt = false;
		int *vcr_pfxd_sat;
		bool *vcr_pfxd_msk;
		bool vcr_pfxd = false;
		long long cycles = 0;
		long long hilo_cycles = 0;
		long long *fpr_cycles;
		long long ***vpr_cycles;
		long long fcr31_cycles = 0;
		AllegrexBasicBlock *current_bb = nullptr;
	protected:
		std::unordered_map<int, AllegrexBasicBlock*> basic_blocks = std::unordered_map<int, AllegrexBasicBlock*>();
	public:
		const bool interpreter_only = true;

	public:
		class RegisterTracking
		{
		private:
			Processor *outerInstance;

		public:
			virtual ~RegisterTracking()
			{
				delete outerInstance;
			}

			RegisterTracking(Processor *outerInstance);


			bool loaded = false; // load the register content if not already done
			bool dirty = false; // save the register content back at basic block termination
			bool fixed = false; // the register helds a constant value
			bool labeled = false; // an associated local variable is created
		};
	public:
		RegisterTracking **tracked_gpr;
		RegisterTracking **tracked_fpr;
		RegisterTracking *tracked_hilo;

		virtual ~Processor()
		{
			delete cpu;
			delete[] gpr;
			delete[] fpr;
			delete[] vpr;
			delete[] vcr_cc;
			delete[] vcr_pfxs_swz;
			delete[] vcr_pfxs_abs;
			delete[] vcr_pfxs_cst;
			delete[] vcr_pfxs_neg;
			delete[] vcr_pfxt_swz;
			delete[] vcr_pfxt_abs;
			delete[] vcr_pfxt_cst;
			delete[] vcr_pfxt_neg;
			delete[] vcr_pfxd_sat;
			delete[] vcr_pfxd_msk;
			delete[] fpr_cycles;
			delete[] vpr_cycles;
			delete current_bb;
			delete[] tracked_gpr;
			delete[] tracked_fpr;
			delete tracked_hilo;
			delete decoder;
		}

		Processor();

		virtual void reset();

		virtual void fix_gpr(int register_Keyword, int value);

		virtual void fix_fpr(int register_Keyword, float value);

		virtual void load_gpr(int register_Keyword, bool force);

		virtual void load_fpr(int register_Keyword, bool force);

		virtual void load_hilo(bool force);

		virtual void alter_gpr(int register_Keyword);

		virtual void alter_fpr(int register_Keyword);

		virtual void alter_hilo();

		virtual std::string get_gpr(int register_Keyword);

		virtual std::string get_fpr(int register_Keyword);

		virtual std::string get_hilo();

		virtual void reset_register_tracking();

		virtual int hi();

		virtual int lo();

		static long long signedDivMod(int x, int y);

		static long long unsignedDivMod(long long x, long long y);

		static int max(int x, int y);


//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
