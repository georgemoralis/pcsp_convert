using namespace std;

#include "AllegrexDecoder.h"

namespace jpcsp
{
	using namespace jpcsp;
//	import static jpcsp.AllegrexOpcodes.*;

	int AllegrexDecoder::rs(int instruction)
	{
		return (instruction >> 21) & 31;
	}

	int AllegrexDecoder::rt(int instruction)
	{
		return (instruction >> 16) & 31;
	}

	int AllegrexDecoder::rd(int instruction)
	{
		return (instruction >> 11) & 31;
	}

	int AllegrexDecoder::sa(int instruction)
	{
		return (instruction >> 6) & 31;
	}

	int AllegrexDecoder::func(int instruction)
	{
		return (instruction & 63);
	}

	int AllegrexDecoder::simm16(int instruction)
	{
		return (instruction << 16) >> 16;
	}

	int AllegrexDecoder::uimm16(int instruction)
	{
		return (instruction) & 0xffff;
	}

	int AllegrexDecoder::uimm24(int instruction)
	{
		return (instruction) & 0x00ffffff;
	}

	int AllegrexDecoder::uimm26(int instruction)
	{
		return (instruction) & 0x03ffffff;
	}

	int AllegrexDecoder::syscode(int instruction)
	{
		return (instruction >> 6) & 0x000fffff;
	}

	int AllegrexDecoder::fd(int instruction)
	{
		return (instruction >> 6) & 31;
	}

	int AllegrexDecoder::fs(int instruction)
	{
		return (instruction >> 11) & 31;
	}

	int AllegrexDecoder::ft(int instruction)
	{
		return (instruction >> 16) & 31;
	}

	int AllegrexDecoder::cond(int instruction)
	{
		return instruction & 15;
	}

	int AllegrexDecoder::vd(int instruction)
	{
		return (instruction) & 127;
	}

	int AllegrexDecoder::vs(int instruction)
	{
		return (instruction >> 8) & 127;
	}

	int AllegrexDecoder::vt(int instruction)
	{
		return (instruction >> 16) & 127;
	}

	int AllegrexDecoder::vt_mem(int instruction)
	{
		return ((instruction >> 16) & 31) | ((instruction & 3) << 5);
	}

	int AllegrexDecoder::uimm3(int instruction)
	{
		return (instruction >> 16) & 7;
	}

	int AllegrexDecoder::uimm5(int instruction)
	{
		return (instruction >> 16) & 31;
	}

	int AllegrexDecoder::vsize(int instruction)
	{
		return 1 + ((instruction >> 7) & 1) + ((instruction >> 15) & 1);
	}

	int AllegrexDecoder::vfpu0(int instruction)
	{
		return (instruction >> 23) & 7;
	}

	int AllegrexDecoder::vfpu1(int instruction)
	{
		return (instruction >> 23) & 7;
	}

	int AllegrexDecoder::vfpu3(int instruction)
	{
		return (instruction >> 23) & 7;
	}

	int AllegrexDecoder::vfpu4(int instruction)
	{
		return (instruction >> 24) & 3;
	}

	int AllegrexDecoder::vfpu4_2(int instruction)
	{
		return (instruction >> 21) & 7;
	}

	int AllegrexDecoder::vfpu5(int instruction)
	{
		return (instruction >> 24) & 3;
	}

	int AllegrexDecoder::vfpu5_3(int instruction)
	{
		return (instruction >> 23) & 1;
	}
}
