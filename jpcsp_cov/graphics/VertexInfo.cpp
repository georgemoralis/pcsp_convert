using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "VertexInfo.h"

namespace jpcsp::graphics
{
	using Emulator = jpcsp::Emulator;
	using Memory = jpcsp::Memory;
int *VertexInfo::size_mapping = new int[4] {0, 1, 2, 4};
string *VertexInfo::texture_info = new string[4] {"", "GU_TEXTURE_8BIT", "GU_TEXTURE_16BIT", "GU_TEXTURE_32BITF"};
string *VertexInfo::color_info = new string[8] {"", "GU_COLOR_UNK2", "GU_COLOR_UNK3", "GU_COLOR_UNK4", "GU_COLOR_5650", "GU_COLOR_5551", "GU_COLOR_4444", "GU_COLOR_8888"};
string *VertexInfo::normal_info = new string[4] {"", "GU_NORMAL_8BIT", "GU_NORMAL_16BIT", "GU_NORMAL_32BITF"};
string *VertexInfo::vertex_info = new string[4] {"", "GU_VERTEX_8BIT", "GU_VERTEX_16BIT", "GU_VERTEX_32BITF"};
string *VertexInfo::weight_info = new string[4] {"", "GU_WEIGHT_8BIT", "GU_WEIGHT_16BIT", "GU_WEIGHT_32BITF"};
string *VertexInfo::index_info = new string[4] {"", "GU_INDEX_8BIT", "GU_INDEX_16BIT", "GU_INDEX_UNK3"};
string *VertexInfo::transform_info = new string[2] {"GU_TRANSFORM_3D", "GU_TRANSFORM_2D"};

	void VertexInfo::processType(int param)
	{
		texture = (param >> 0) & 0x3;
		color = (param >> 2) & 0x7;
		normal = (param >> 5) & 0x3;
		position = (param >> 7) & 0x3;
		weight = (param >> 9) & 0x3;
		index = (param >> 11) & 0x3;
		skinningWeightCount = ((param >> 14) & 0x7) + 1;
		morphingVertexCount = (param >> 18) & 0x3;
		transform2D = (param >> 23) & 0x1;

		vertexSize = 0;
		vertexSize += size_mapping[weight] * skinningWeightCount;
		vertexSize += (color != 0) ? ((color == 7) ? 4 : 2) : 0;
		vertexSize += size_mapping[texture] * 2;
		vertexSize += size_mapping[position] * 3;
		vertexSize += size_mapping[normal] * 3;
	}

	int VertexInfo::getAddress(int i)
	{
		if (ptr_index != 0)
		{
			int addr = ptr_index + i * index;
			switch (index)
			{
				case 1:
					i = Emulator::getMemory()->read8(addr);
					break;
				case 2:
					i = Emulator::getMemory()->read16(addr);
					break;
				case 4:
					i = Emulator::getMemory()->read32(addr);
					break;
			}
		}

		return ptr_vertex + i * vertexSize;
	}

	VertexState *VertexInfo::readVertex(Memory *mem, int addr)
	{
		VertexState *v = new VertexState();

		switch (texture)
		{
			case 1:
				v->u = Emulator::getMemory()->read8(addr);
				addr += 1;
				v->v = Emulator::getMemory()->read8(addr);
				addr += 1;
				break;
			case 2:
				v->u = Emulator::getMemory()->read16(addr);
				addr += 2;
				v->v = Emulator::getMemory()->read16(addr);
				addr += 2;
				break;
			case 3:
				v->u = Float::intBitsToFloat(mem->read32(addr));
				addr += 4;
				v->v = Float::intBitsToFloat(mem->read32(addr));
				addr += 4;
				break;
		}

		switch (color)
		{
			case 1:
		case 2:
	case 3:
		cout << "unimplemented color type" << endl;
		addr += 1;
		break;
			case 4:
		case 5:
	case 6:
		cout << "unimplemented color type" << endl;
		addr += 2;
		break;
			case 7:
			{ // GU_COLOR_8888
				int packed = mem->read32(addr);
				addr += 4;
				v->r = static_cast<float>((packed) & 0xff) / 255;
				v->g = static_cast<float>((packed >> 8) & 0xff) / 255;
				v->b = static_cast<float>((packed >> 16) & 0xff) / 255;
				v->a = static_cast<float>((packed >> 24) & 0xff) / 255;
				break;
			}
		}

		switch (normal)
		{
			case 1:
				v->nx = Emulator::getMemory()->read8(addr);
				addr += 1;
				v->ny = Emulator::getMemory()->read8(addr);
				addr += 1;
				v->nz = Emulator::getMemory()->read8(addr);
				addr += 1;
				break;
			case 2:
				v->nx = Emulator::getMemory()->read16(addr);
				addr += 2;
				v->ny = Emulator::getMemory()->read16(addr);
				addr += 2;
				v->nz = Emulator::getMemory()->read16(addr);
				addr += 2;

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
