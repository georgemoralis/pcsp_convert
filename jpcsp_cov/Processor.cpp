using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "Processor.h"
#include "Memory.h"
#include "Allegrex/Common.h"
#include "Allegrex/Decoder.h"

namespace jpcsp
{
	using SyscallHandler = jpcsp::HLE::SyscallHandler;
	using namespace jpcsp::Allegrex;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;

	Processor::RegisterTracking::RegisterTracking(Processor *outerInstance) : outerInstance(outerInstance)
	{
	}

	Processor::Processor()
	{
		Memory::get_instance(); //intialize memory
		reset();
		testOpcodes();
		reset();
	}

	void Processor::reset()
	{
		// intialize psp register
		pc = npc = 0x00000000;
		hilo = 0;
		gpr = new int[32];
		fpr = new float[32];
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: vpr = new float[8][4][4];
		vpr = RectangularArrays::RectangularFloatArray(8, 4, 4); // [matrix][column][row]

		fcr31_rm = 0;
		fcr31_c = false;
		fcr31_fs = false;

		vcr_cc = new bool[6];

		cycles = 0;
		hilo_cycles = 0;
		fpr_cycles = new long long[32];
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: vpr_cycles = new long[8][4][4];
		vpr_cycles = RectangularArrays::RectangularLongLongArray(8, 4, 4);

		tracked_gpr = new RegisterTracking*[32];
		tracked_fpr = new RegisterTracking*[32];
		tracked_hilo = new RegisterTracking(this);

		reset_register_tracking();

		if (false)
		{
			for (auto insn : Common::instructions())
			{
				if (insn != nullptr)
				{
					insn->resetCount();
				}
			}
		}
	}

	void Processor::fix_gpr(int register_Keyword, int value)
	{
		if (register_Keyword != 0 || current_bb != nullptr)
		{
			tracked_gpr[register_Keyword]->loaded = false;
			tracked_gpr[register_Keyword]->dirty = true;
			tracked_gpr[register_Keyword]->fixed = true;
			gpr[register_Keyword] = value;
		}
	}

	void Processor::fix_fpr(int register_Keyword, float value)
	{
		if (register_Keyword != 0 || current_bb != nullptr)
		{
			tracked_fpr[register_Keyword]->loaded = false;
			tracked_fpr[register_Keyword]->dirty = true;
			tracked_fpr[register_Keyword]->fixed = true;
			fpr[register_Keyword] = value;
		}
	}

	void Processor::load_gpr(int register_Keyword, bool force)
	{
		if (register_Keyword != 0 && current_bb != nullptr)
		{
			if (!force && tracked_gpr[register_Keyword]->fixed)
			{
				return;
			}
			if (!tracked_gpr[register_Keyword]->labeled)
			{
				current_bb->emit("int gpr_" + to_string(register_Keyword) + " = processor.gpr[" + to_string(register_Keyword) + "];");
				tracked_gpr[register_Keyword]->labeled = true;
			}
			tracked_gpr[register_Keyword]->loaded = true;
			tracked_gpr[register_Keyword]->dirty = false;
			tracked_gpr[register_Keyword]->fixed = false;
		}
	}

	void Processor::load_fpr(int register_Keyword, bool force)
	{
		if (register_Keyword != 0 && current_bb != nullptr)
		{
			if (!force && tracked_fpr[register_Keyword]->fixed)
			{
				return;
			}
			if (!tracked_fpr[register_Keyword]->labeled)
			{
				current_bb->emit("int fpr_" + to_string(register_Keyword) + " = processor.fpr[" + to_string(register_Keyword) + "];");
				tracked_fpr[register_Keyword]->labeled = true;
			}
			tracked_fpr[register_Keyword]->loaded = true;
			tracked_fpr[register_Keyword]->dirty = false;
			tracked_fpr[register_Keyword]->fixed = false;
		}
	}

	void Processor::load_hilo(bool force)
	{
		if (current_bb != nullptr)
		{
			if (!force && tracked_hilo->fixed)
			{
				return;
			}
			if (!tracked_hilo->labeled)
			{
				current_bb->emit("long hilo = processor.hilo;");
				tracked_hilo->labeled = true;
			}
			tracked_hilo->loaded = true;
			tracked_hilo->dirty = false;
			tracked_hilo->fixed = false;
		}
	}

	void Processor::alter_gpr(int register_Keyword)
	{
		if (register_Keyword != 0 && current_bb != nullptr)
		{
			if (!tracked_gpr[register_Keyword]->labeled)
			{
				current_bb->emit("int gpr_" + to_string(register_Keyword) + ";");
				tracked_gpr[register_Keyword]->labeled = true;
			}
			tracked_gpr[register_Keyword]->loaded = false;
			tracked_gpr[register_Keyword]->dirty = true;
			tracked_gpr[register_Keyword]->fixed = false;
		}
	}

	void Processor::alter_fpr(int register_Keyword)
	{
		if (register_Keyword != 0 && current_bb != nullptr)
		{
			if (!tracked_fpr[register_Keyword]->labeled)
			{
				current_bb->emit("float fpr_" + to_string(register_Keyword) + ";");
				tracked_fpr[register_Keyword]->labeled = true;
			}
			tracked_fpr[register_Keyword]->loaded = false;
			tracked_fpr[register_Keyword]->dirty = true;
			tracked_fpr[register_Keyword]->fixed = false;
		}
	}

	void Processor::alter_hilo()
	{
		if (current_bb != nullptr)
		{
			if (!tracked_hilo->labeled)
			{
				current_bb->emit("long hilo;");
				tracked_hilo->labeled = true;
			}
			tracked_hilo->loaded = false;
			tracked_hilo->dirty = true;
			tracked_hilo->fixed = false;
		}
	}

	string Processor::get_gpr(int register_Keyword)
	{

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
