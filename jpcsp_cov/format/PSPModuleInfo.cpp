using namespace std;

#include "PSPModuleInfo.h"
#include "../util/Utilities.h"

namespace jpcsp::format
{
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;

	void PSPModuleInfo::read(ByteBuffer *f)
	{
		m_attr = Utilities::readUHalf(f);
		m_version = Utilities::readUHalf(f);
		f->get(m_name);
		m_gp = Utilities::readUWord(f);
		m_exports = Utilities::readUWord(f); // .lib.ent

		m_exp_end = Utilities::readUWord(f);
		m_imports = Utilities::readUWord(f); // .lib.stub

		m_imp_end = Utilities::readUWord(f);

		// Convert the array of bytes used for the module name to a Java String
		// Calculate the length of the printable portion of the string, otherwise
		// any extra trailing characters may be printed as garbage.
		int len = 0;
		while (len < 28 && m_name[len] != 0)
		{
			len++;
		}
		m_namez = string(m_name, 0, len);
	}

	int PSPModuleInfo::getM_attr()
	{
		return m_attr;
	}

	int PSPModuleInfo::getM_version()
	{
		return m_version;
	}

	signed char *PSPModuleInfo::getM_name()
	{
		return m_name;
	}

	long long PSPModuleInfo::getM_gp()
	{
		return m_gp;
	}

	long long PSPModuleInfo::getM_exports()
	{
		return m_exports;
	}

	long long PSPModuleInfo::getM_exp_end()
	{
		return m_exp_end;
	}

	long long PSPModuleInfo::getM_imports()
	{
		return m_imports;
	}

	long long PSPModuleInfo::getM_imp_end()
	{
		return m_imp_end;
	}

	string PSPModuleInfo::getM_namez()
	{
		return m_namez;
	}
}
