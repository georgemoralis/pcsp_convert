#pragma once

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
namespace jpcsp::format
{

	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using namespace jpcsp::util;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;
	class PSPModuleInfo
	{

	private:
		int m_attr = 0;
		int m_version = 0;
		signed char *m_name = new signed char[28];
		long long m_gp = 0;
		long long m_exports = 0;
		long long m_exp_end = 0;
		long long m_imports = 0;
		long long m_imp_end = 0;
		std::string m_namez = ""; // String version of m_name


	public:
		virtual ~PSPModuleInfo()
		{
			delete[] m_name;
		}

		virtual void read(ByteBuffer *f);

		virtual int getM_attr();

		virtual int getM_version();

		virtual signed char *getM_name();

		virtual long long getM_gp();

		virtual long long getM_exports();

		virtual long long getM_exp_end();

		virtual long long getM_imports();

		virtual long long getM_imp_end();

		virtual std::string getM_namez();
	};

}
