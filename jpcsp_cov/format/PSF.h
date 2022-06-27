#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <any>
#include <optional>
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

	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using HashMap = java::util::HashMap;

	using namespace jpcsp::util;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;
	/**
	 *
	 * @author George
	 */
	class PSF
	{
	 private:
		 long long p_offset_param_sfo = 0; //offset of param.sfo in pbp
		 const long long psfident = 0x46535000;

		 long long fileidentify = 0;
		 long long psfversion = 0;
		 long long offsetkeytable = 0;
		 long long offsetvaluetable = 0;
		 long long numberofkeypairs = 0;

		 //index table
		 /*
	0 	1 	2 	ul16 Offset of the key name into the key table (in bytes)
	2 	2 	1 	4 Unknown, always 4. Maybe alignment requirement for the data?
	3 	3 	1 	ul8 Datatype of the value, see below.
	4 	7 	4 	ul32 Size of value data, in bytes
	8 	11 	4 	ul32 Size of value data plus padding, in bytes
	12 	15 	4 	ul32 Offset of the data value into the value table (in bytes) */
		 int *offset_keyname;
		 signed char *alignment;
		 signed char *datatype;
		 long long *value_size;
		 long long *value_size_padding;
		 long long *offset_data_value;

	 public:
		 std::unordered_map<std::string, std::any> map = std::unordered_map<std::string, std::any>();

		 virtual ~PSF()
		 {
			 delete[] offset_keyname;
			 delete[] alignment;
			 delete[] datatype;
			 delete[] value_size;
			 delete[] value_size_padding;
			 delete[] offset_data_value;
		 }

		 PSF(long long p_offset_param_sfo);
		 virtual void read(ByteBuffer *f);

		 virtual std::string toString();

		 virtual std::any get(const std::string &key);

		 virtual std::string getString(const std::string &key);

		 virtual long long getNumeric(const std::string &key);
	};

}
