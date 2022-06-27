using namespace std;

#include "PSP.h"
#include "../util/Utilities.h"

namespace jpcsp::format
{
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using namespace jpcsp::filesystems;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;

	void PSP::read(ByteBuffer *f)
	{
		e_magic = Utilities::readUWord(f);
	}

	PSP::PSP(ByteBuffer *f)
	{
		read(f);
	}

	bool PSP::isValid()
	{
	   return (Long::toHexString(e_magic & 0xFFFFFFFFLL)->toUpperCase().equals("5053507E")); //~PSP
	}
}
