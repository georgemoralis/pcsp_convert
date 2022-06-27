using namespace std;

#include "GeDecoder.h"

namespace jpcsp::graphics
{
	using namespace jpcsp::graphics;
//	import static jpcsp.graphics.GeCommands.*;

	int GeDecoder::intArgument(int word)
	{
		return (word & 0x00FFFFFF);
	}

	float GeDecoder::floatArgument(int word)
	{
		return Float::intBitsToFloat(word << 8);
	}
}
