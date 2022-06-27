using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "Decoder.h"

namespace jpcsp::Allegrex
{

const Instruction **Decoder::table_0 = new jpcsp::Allegrex::Common::Instruction*[64]
{
	new jpcsp::Allegrex::Common::STUB()
	{
		jpcsp::Allegrex::Common::Instruction instance(int insn) {return table_1[(insn >> 0) & 0x0000003f]->instance(insn);}
	},
	new jpcsp::Allegrex::Common::STUB()
	{
		public jpcsp::Allegrex::Common::Instruction instance(int insn) {return table_2[(insn >> 16) & 0x00000003]->instance(insn);}
	},
	jpcsp::Allegrex::Instructions::J,
	jpcsp::Allegrex::Instructions::JAL,
	jpcsp::Allegrex::Instructions::BEQ,
	jpcsp::Allegrex::Instructions::BNE,
	jpcsp::Allegrex::Instructions::BLEZ,
	jpcsp::Allegrex::Instructions::BGTZ,
	jpcsp::Allegrex::Instructions::ADDI,
	jpcsp::Allegrex::Instructions::ADDIU,
	jpcsp::Allegrex::Instructions::SLTI,
	jpcsp::Allegrex::Instructions::SLTIU,
	jpcsp::Allegrex::Instructions::ANDI,
	jpcsp::Allegrex::Instructions::ORI,
	jpcsp::Allegrex::Instructions::XORI,
	jpcsp::Allegrex::Instructions::LUI,
	new jpcsp::Allegrex::Common::STUB()
	{
		public jpcsp::Allegrex::Common::Instruction instance(int insn) {return table_3[(insn >> 22) & 0x00000003]->instance(insn);}
	},
	new jpcsp::Allegrex::Common::STUB()
	{
		public jpcsp::Allegrex::Common::Instruction instance(int insn) {return table_4[(insn >> 23) & 0x00000007]->instance(insn);}
	},
	new jpcsp::Allegrex::Common::STUB()
	{
		public jpcsp::Allegrex::Common::Instruction instance(int insn)
		{
			if ((insn & 0x00200000) == 0x00000000) {return table_7[(insn >> 16) & 0x00000003]->instance(insn);} else
			{
				if ((insn & 0x00000080) == 0x00000000)
				{
					if ((insn & 0x00800000) == 0x00000000) {return jpcsp::Allegrex::Instructions::MFV;} else {return jpcsp::Allegrex::Instructions::MTV;}
				}
				else
				{
					if ((insn & 0x00800000) == 0x00000000) {return jpcsp::Allegrex::Instructions::MFVC;} else {return jpcsp::Allegrex::Instructions::MTVC;}
				}
			}
		}
	},
	jpcsp::Allegrex::Common::UNK,
	jpcsp::Allegrex::Instructions::BEQL,
	jpcsp::Allegrex::Instructions::BNEL,
	jpcsp::Allegrex::Instructions::BLEZL,
	jpcsp::Allegrex::Instructions::BGTZL,
	new jpcsp::Allegrex::Common::STUB()
	{
		public jpcsp::Allegrex::Common::Instruction instance(int insn) {return table_8[(insn >> 23) & 0x00000003]->instance(insn);}
	},
	new jpcsp::Allegrex::Common::STUB()
	{
		public jpcsp::Allegrex::Common::Instruction instance(int insn) {return table_9[(insn >> 23) & 0x00000007]->instance(insn);}
	},
	jpcsp::Allegrex::Common::UNK,
	new jpcsp::Allegrex::Common::STUB()
	{
		public jpcsp::Allegrex::Common::Instruction instance(int insn) {return table_10[(insn >> 23) & 0x00000007]->instance(insn);}
	},
	jpcsp::Allegrex::Common::UNK,
	jpcsp::Allegrex::Common::UNK,
	jpcsp::Allegrex::Common::UNK,
	new jpcsp::Allegrex::Common::STUB()
	{
		public jpcsp::Allegrex::Common::Instruction instance(int insn)
		{
			if ((insn & 0x00000021) == 0x00000020)
			{
				if ((insn & 0x00000080) == 0x00000000)
				{
					if ((insn & 0x00000100) == 0x00000000) {return jpcsp::Allegrex::Instructions::SEH;} else {return jpcsp::Allegrex::Instructions::BITREV;}
				}
				else
				{
					if ((insn & 0x00000040) == 0x00000000) {return jpcsp::Allegrex::Instructions::WSBH;} else {return jpcsp::Allegrex::Instructions::WSBW;}
				}
			}
			else
			{
				if ((insn & 0x00000001) == 0x00000000)
				{
					if ((insn & 0x00000004) == 0x00000000) {return jpcsp::Allegrex::Instructions::EXT;} else {return jpcsp::Allegrex::Instructions::INS;}
				}
				else {return jpcsp::Allegrex::Instructions::SEB;}
			}
		}
	},
	jpcsp::Allegrex::Instructions::LB,
	jpcsp::Allegrex::Instructions::LH,
	jpcsp::Allegrex::Instructions::LWL,
	jpcsp::Allegrex::Instructions::LW,
	jpcsp::Allegrex::Instructions::LBU,
	jpcsp::Allegrex::Instructions::LHU,
	jpcsp::Allegrex::Instructions::LWR,
	jpcsp::Allegrex::Common::UNK,
	jpcsp::Allegrex::Instructions::SB,
	jpcsp::Allegrex::Instructions::SH,
	jpcsp::Allegrex::Instructions::SWL,
	jpcsp::Allegrex::Instructions::SW,
	jpcsp::Allegrex::Common::UNK,
	jpcsp::Allegrex::Common::UNK,
	jpcsp::Allegrex::Instructions::SWR,
	new jpcsp::Allegrex::Common::STUB()
	{
		public jpcsp::Allegrex::Common::Instruction instance(int insn) {return table_11[(insn >> 17) & 0x0000000f]->instance(insn);}
	},
	jpcsp::Allegrex::Instructions::LL,
	jpcsp::Allegrex::Instructions::LWC1,
	jpcsp::Allegrex::Instructions::LVS,
	jpcsp::Allegrex::Common::UNK,

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
