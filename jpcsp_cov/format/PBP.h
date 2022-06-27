#pragma once

#include "Elf32.h"
#include "PSF.h"
#include <string>
#include "../stringbuilder.h"

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

	using File = java::io::File;
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using namespace jpcsp::filesystems;
	using namespace jpcsp::util;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;

	class PBP
	{
	private:
		static constexpr long long PBP_MAGIC = 0x50425000LL;
		static const std::string PBP_UNPACK_PATH_PREFIX;

		std::string info;

		int size_pbp = 0;
		int size_param_sfo = 0;
		int size_icon0_png = 0;
		int size_icon1_pmf = 0;
		int size_pic0_png = 0;
		int size_pic1_png = 0;
		int size_snd0_at3 = 0;
		int size_psp_data = 0;
		int size_psar_data = 0;

		long long p_magic = 0;
		long long p_version = 0;
		long long p_offset_param_sfo = 0;
		long long p_offset_icon0_png = 0;
		long long p_offset_icon1_pmf = 0;
		long long p_offset_pic0_png = 0;
		long long p_offset_pic1_png = 0;
		long long p_offset_snd0_at3 = 0;
		long long p_offset_psp_data = 0;
		long long p_offset_psar_data = 0;
		Elf32 *elf32;

	public:
		virtual ~PBP()
		{
			delete elf32;
		}

		virtual bool isValid();

		virtual void setElf32(Elf32 *elf);

		virtual Elf32 *getElf32();

		virtual void setInfo(const std::string &msg);

		virtual std::string getInfo();

		PBP(ByteBuffer *f);
		virtual PSF *readPSF(ByteBuffer *f);
		virtual std::string toString();

		virtual long long getMagic();

		virtual long long getVersion();

		virtual long long getOffsetParam();

		virtual long long getOffsetIcon0();

		virtual long long getOffsetIcon1();

		virtual long long getOffsetPic0();

		virtual long long getOffsetPic1();

		virtual long long getOffsetSnd0();

		virtual long long getOffsetPspData();

		virtual long long getOffsetPsarData();

		virtual int getSizeIcon0();

		static bool deleteDir(File *dir);

		static void unpackPBP(ByteBuffer *f);
	};

}
