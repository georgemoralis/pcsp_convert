#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "GeCommands.h"
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
namespace jpcsp::graphics
{

	using namespace jpcsp::graphics;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.graphics.GeCommands.*;

	/**
	 *
	 * @author hli
	 */
	class GeDecoder
	{

	private:
		int intArgument(int word);

		float floatArgument(int word);

	public:
		template<typename P>
		void process(P that, int insn)
		{
			static_assert(std::is_base_of<GeCommands, P>::value, "P must inherit from GeCommands");


			int command = (static_cast<int>(static_cast<unsigned int>(insn) >> 24));

			switch (command)
			{
				case GeCommands::NOP:
					break;
				case GeCommands::VADDR:
					break;
				case GeCommands::IADDR:
					break;
				case GeCommands::PRIM:
					break;
				case GeCommands::BEZIER:
					break;
				case GeCommands::SPLINE:
					break;
				case GeCommands::BBOX:
					break;
				case GeCommands::JUMP:
					break;
				case GeCommands::BJUMP:
					break;
				case GeCommands::CALL:
					break;
				case GeCommands::RET:
					break;
				case GeCommands::END:
					break;
				case GeCommands::SIGNAL:
					break;
				case GeCommands::FINISH:
					break;
				case GeCommands::BASE:
					break;
				case GeCommands::VTYPE:
					break;
				case GeCommands::OFFSET_ADDR:
					break;
				case GeCommands::ORIGIN_ADDR:
					break;
				case GeCommands::REGION1:
					break;
				case GeCommands::REGION2:
					break;
				case GeCommands::LTE:
					break;
				case GeCommands::LTE0:
					break;
				case GeCommands::LTE1:
					break;
				case GeCommands::LTE2:
					break;
				case GeCommands::LTE3:
					break;
				case GeCommands::CPE:
					break;
				case GeCommands::BCE:
					break;
				case GeCommands::TME:
					break;
				case GeCommands::FGE:
					break;
				case GeCommands::DTE:
					break;
				case GeCommands::ABE:
					break;
				case GeCommands::ATE:
					break;
				case GeCommands::ZTE:
					break;
				case GeCommands::STE:
					break;
				case GeCommands::AAE:
					break;
				case GeCommands::PCE:
					break;
				case GeCommands::CTE:
					break;
				case GeCommands::LOE:
					break;
				case GeCommands::BOFS:
					break;
				case GeCommands::BONE:
					break;
				case GeCommands::MW0:
					break;
				case GeCommands::MW1:
					break;
				case GeCommands::MW2:
					break;
				case GeCommands::MW3:
					break;
				case GeCommands::MW4:

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
