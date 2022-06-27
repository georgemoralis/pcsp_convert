#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <string>

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

	class GeCommands
	{

	private:
		std::string *commands;

	public:
		static constexpr int NOP = 0x00; //    No Operation
		static constexpr int VADDR = 0x01; //     Vertex List (BASE)
		static constexpr int IADDR = 0x02; //    Index List (BASE)
		static constexpr int PRIM = 0x04; //Primitive Kick
			static constexpr int PRIM_POINT = 0x00;
			static constexpr int PRIM_LINE = 0x01;
			static constexpr int PRIM_LINES_STRIPS = 0x02;
			static constexpr int PRIM_TRIANGLE = 0x03;
			static constexpr int PRIM_TRIANGLE_STRIPS = 0x04;
			static constexpr int PRIM_TRIANGLE_FANS = 0x05;
			static constexpr int PRIM_SPRITES = 0x06;
		static constexpr int BEZIER = 0x05; //Bezier Patch Kick
		static constexpr int SPLINE = 0x06; //Spline Surface Kick
			static constexpr int SPLINE_EDGE_CLOSE_CLOSE = 0x0; //V OR U IS THE SAME
			static constexpr int SPLINE_EDGE_OPEN_CLOSE = 0x1; //V OR U IS THE SAME
			static constexpr int SPLINE_EDGE_CLOSE_OPEN = 0x2; //V OR U IS THE SAME
			static constexpr int SPLINE_EDGE_OPEN_OPEN = 0x3; //V OR U IS THE SAME
		static constexpr int BBOX = 0x07; //Bounding Box
		static constexpr int JUMP = 0x08; //Jump To New Address (BASE)
		static constexpr int BJUMP = 0x09; //Conditional Jump (BASE)
		static constexpr int CALL = 0x0A; //Call Address (BASE)
		static constexpr int RET = 0x0B; //Return From Call
		static constexpr int END = 0x0C; //Stop Execution
		static constexpr int UNKNOWCOMMAND_0X0D = 0x0D;
		static constexpr int SIGNAL = 0x0E; //    SIGNAL     Raise Signal Interrupt
		static constexpr int FINISH = 0x0F; //     FINISH     Complete Rendering
		static constexpr int BASE = 0x10; //BASE     Base Address Register
		static constexpr int UNKNOWCOMMAND_0X11 = 0x11;
		static constexpr int VTYPE = 0x12; //     VTYPE     Vertex Type
			static constexpr int VTYPE_TRANSFORM_PIPELINE_TRANS_COORD = 0x0;
			static constexpr int VTYPE_TRANSFORM_PIPELINE_RAW_COORD = 0x1;

			static constexpr int VTYPE_INDEX_NOT_USING_INDEX = 0x00;
			static constexpr int VTYPE_INDEX_8_BIT = 0x01;
			static constexpr int VTYPE_INDEX_16_BIT = 0x02;
			static constexpr int VTYPE_INDEX_UNKNOW = 0x03;

			static constexpr int VTYPE_WEIGTH_FORMAT_NOT_PRESENT = 0x00;
			static constexpr int VTYPE_WEIGTH_FORMAT_8_BIT = 0x01;
			static constexpr int VTYPE_WEIGTH_FORMAT_16_BIT = 0x02;
			static constexpr int VTYPE_WEIGTH_FORMAT_32_BIT = 0x03;

			static constexpr int VTYPE_POSITION_FORMAT_NOT_PRESENT = 0x00;
			static constexpr int VTYPE_POSITION_FORMAT_8_BIT = 0x01;
			static constexpr int VTYPE_POSITION_FORMAT_16_BIT = 0x02;
			static constexpr int VTYPE_POSITION_FORMAT_36_BIT = 0x03;

			static constexpr int VTYPE_NORMAL_FORMAT_NOT_PRESENT = 0x00;
			static constexpr int VTYPE_NORMAL_FORMAT_8_BIT = 0x01;
			static constexpr int VTYPE_NORMAL_FORMAT_16_BIT = 0x02;
			static constexpr int VTYPE_NORMAL_FORMAT_32_BIT = 0x03;

			static constexpr int VTYPE_COLOR_FORMAT_NOT_PRESENT = 0x00;
			static constexpr int VTYPE_COLOR_FORMAT_UNK_0X01 = 0x01;
			static constexpr int VTYPE_COLOR_FORMAT_UNK_0X02 = 0X02;
			static constexpr int VTYPE_COLOR_FORMAT_UNK_0X03 = 0X03;
			static constexpr int VTYPE_COLOR_FORMAT_16BIT_BGR_5650 = 0X04;
			static constexpr int VTYPE_COLOR_FORMAT_16BIT_ABGR_5551 = 0X05;
			static constexpr int VTYPE_COLOR_FORMAT_16BIT_ABGR_4444 = 0X06;
			static constexpr int VTYPE_COLOR_FORMAT_32BIT_ABGR_8888 = 0X07;

			static constexpr int VTYPE_TEXTURE_FORMAT_NOT_PRESENT = 0X00;
			static constexpr int VTYPE_TEXTURE_FORMAT_8_BIT = 0X01;
			static constexpr int VTYPE_TEXTURE_FORMAT_16_BIT = 0X02;
			static constexpr int VTYPE_TEXTURE_FORMAT_32_BIT = 0X03;
		static constexpr int OFFSET_ADDR = 0x13; //???     Offset Address (BASE)
		static constexpr int ORIGIN_ADDR = 0x14; //???     Origin Address (BASE)
		static constexpr int REGION1 = 0x15; //     REGION1     Draw Region Start
		static constexpr int REGION2 = 0x16; //     REGION2     Draw Region End
		static constexpr int LTE = 0x17; //     LTE     Lighting Enable
		static constexpr int LTE0 = 0x18; //     LTE0     Light 0 Enable
		static constexpr int LTE1 = 0x19; //     LTE1     Light 1 Enable
		static constexpr int LTE2 = 0x1A; //     LTE2     Light 2 Enable
		static constexpr int LTE3 = 0x1B; //     LTE3     Light 3 Enable
		static constexpr int CPE = 0x1C; //     CPE     Clip Plane Enable
		static constexpr int BCE = 0x1D; //     BCE     Backface Culling Enable
		static constexpr int TME = 0x1E; //     TME     Texture Mapping Enable
		static constexpr int FGE = 0x1F; //     FGE     Fog Enable
		static constexpr int DTE = 0x20; //     DTE     Dither Enable
		static constexpr int ABE = 0x21; //     ABE     Alpha Blend Enable
		static constexpr int ATE = 0x22; //     ATE     Alpha Test Enable
		static constexpr int ZTE = 0x23; //     ZTE     Depth Test Enable
		static constexpr int STE = 0x24; //     STE     Stencil Test Enable
		static constexpr int AAE = 0x25; //     AAE     Anitaliasing Enable
		static constexpr int PCE = 0x26; //     PCE     Patch Cull Enable
		static constexpr int CTE = 0x27; //     CTE     Color Test Enable
		static constexpr int LOE = 0x28; //     LOE     Logical Operation Enable
		static constexpr int UNKNOWCOMMAND_0x29 = 0x29;
		static constexpr int BOFS = 0x2A; //     BOFS     Bone Matrix Offset
		static constexpr int BONE = 0x2B; //     BONE     Bone Matrix Upload
		static constexpr int MW0 = 0x2C; //     MW0     Morph Weight 0
		static constexpr int MW1 = 0x2D; //     MW1     Morph Weight 1
		static constexpr int MW2 = 0x2E; //     MW2     Morph Weight 2
		static constexpr int MW3 = 0x2F; //     MW3     Morph Weight 3
		static constexpr int MW4 = 0x30; //     MW4     Morph Weight 4
		static constexpr int MW5 = 0x31; //     MW5     Morph Weight 5
		static constexpr int MW6 = 0x32; //     MW6     Morph Weight 6
		static constexpr int MW7 = 0x33; //     MW7     Morph Weight 7
		static constexpr int UNKNOWCOMMAND_0x34 = 0x34;
		static constexpr int UNKNOWCOMMAND_0x35 = 0x35;
		static constexpr int PSUB = 0x36; //     PSUB     Patch Subdivision

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
