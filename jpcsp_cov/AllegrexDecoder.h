#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "AllegrexOpcodes.h"
#include <type_traits>

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

	using namespace jpcsp;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.AllegrexOpcodes.*;

	/**
	 *
	 * @author hli
	 */
	class AllegrexDecoder
	{

	public:
		virtual int rs(int instruction);

		virtual int rt(int instruction);

		virtual int rd(int instruction);

		virtual int sa(int instruction);

		virtual int func(int instruction);

		virtual int simm16(int instruction);

		virtual int uimm16(int instruction);

		virtual int uimm24(int instruction);

		virtual int uimm26(int instruction);

		virtual int syscode(int instruction);

		virtual int fd(int instruction);

		virtual int fs(int instruction);

		virtual int ft(int instruction);

		virtual int cond(int instruction);

		virtual int vd(int instruction);

		virtual int vs(int instruction);

		virtual int vt(int instruction);

		virtual int vt_mem(int instruction);

		virtual int uimm3(int instruction);

		virtual int uimm5(int instruction);

		virtual int vsize(int instruction);

		virtual int vfpu0(int instruction);

		virtual int vfpu1(int instruction);

		virtual int vfpu3(int instruction);

		virtual int vfpu4(int instruction);

		virtual int vfpu4_2(int instruction);

		virtual int vfpu5(int instruction);

		virtual int vfpu5_3(int instruction);

		template<typename P>
		void process(P that, int insn)
		{
			static_assert(std::is_base_of<AllegrexInstructions, P>::value, "P must inherit from AllegrexInstructions");


			signed char opcode = static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(insn) >> 26));

			switch (opcode)
			{
				case AllegrexOpcodes::SPECIAL:
					switch (static_cast<signed char>(func(insn)))
					{
						case AllegrexOpcodes::SLL:
							if (insn == 0)
							{
								that->doNOP();
							}
							else
							{
								that->doSLL(rd(insn), rt(insn), sa(insn));
							}
							break;

						case AllegrexOpcodes::SRLROR:
							if (rs(insn) == AllegrexOpcodes::ROTR)
							{
								that->doROTR(rd(insn), rt(insn), sa(insn));
							}
							else
							{
								that->doSRL(rd(insn), rt(insn), sa(insn));
							}
							break;

						case AllegrexOpcodes::SRA:
							that->doSRA(rd(insn), rt(insn), sa(insn));
							break;

						case AllegrexOpcodes::SLLV:
							that->doSLLV(rd(insn), rt(insn), rs(insn));
							break;

						case AllegrexOpcodes::SRLRORV:
							if (sa(insn) == AllegrexOpcodes::ROTRV)
							{
								that->doROTRV(rd(insn), rt(insn), rs(insn));
							}
							else
							{
								that->doSRLV(rd(insn), rt(insn), rs(insn));
							}
							break;

						case AllegrexOpcodes::SRAV:
							that->doSRAV(rd(insn), rt(insn), rs(insn));
							break;

						case AllegrexOpcodes::JR:
							that->doJR(rs(insn));
							break;

						case AllegrexOpcodes::JALR:
							that->doJALR(rd(insn), rs(insn));
							break;

						case AllegrexOpcodes::MOVZ:
							that->doMOVZ(rd(insn), rs(insn), rt(insn));
							break;

						case AllegrexOpcodes::MOVN:
							that->doMOVN(rd(insn), rs(insn), rt(insn));
							break;

						case AllegrexOpcodes::SYSCALL:
						{
							that->doSYSCALL(syscode(insn));
							break;
						}

						case AllegrexOpcodes::BREAK:
						{
							that->doBREAK(syscode(insn));
							break;
						}
						case AllegrexOpcodes::SYNC:
							that->doSYNC();
							break;

						case AllegrexOpcodes::MFHI:
							that->doMFHI(rd(insn));
							break;

						case AllegrexOpcodes::MTHI:
							that->doMTHI(rs(insn));
							break;

						case AllegrexOpcodes::MFLO:
							that->doMFLO(rd(insn));
							break;

						case AllegrexOpcodes::MTLO:
							that->doMTLO(rs(insn));
							break;

						case AllegrexOpcodes::CLZ:

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
