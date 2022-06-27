#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "../Memory.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <utility>
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
	using Memory = jpcsp::Memory;
	using namespace jpcsp::util;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;

	class Elf32SectionHeader
	{

	private:
		std::string sh_namez = "";
		long long sh_name = 0;
		int sh_type = 0;
		int sh_flags = 0;
		long long sh_addr = 0;
		long long sh_offset = 0;
		long long sh_size = 0;
		int sh_link = 0;
		int sh_info = 0;
		int sh_addralign = 0;
		long long sh_entsize = 0;

		static int sizeof_Keyword();

	public:
		Elf32SectionHeader(ByteBuffer *f);

		Elf32SectionHeader(Memory *mem, int address);

		virtual std::string toString();

		virtual std::string getSh_namez();

		virtual void setSh_namez(const std::string &sh_namez);

		virtual long long getSh_name();

		virtual int getSh_type();

		virtual int getSh_flags();

		virtual long long getSh_addr();

		virtual long long getSh_offset();

		virtual long long getSh_size();

		virtual int getSh_link();

		virtual int getSh_info();

		virtual int getSh_addralign();

		virtual long long getSh_entsize();

	public:
		enum class ShFlags
		{
			None = 0,
			Write = 1,
			Allocate = 2,
			Execute = 4

//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//			private int value;
//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//			private ShFlags(int val)
	//		{
	//			value=val;
	//		}
//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//			public int getValue()
	//		{
	//			return value;
	//		}
		};

		class ShFlagsHelper
		{
		private:
			static std::vector<std::pair<ShFlags, std::string>> pairs()
			{
				return
				{
					{ShFlags::None, "None"},
					{ShFlags::Write, "Write"},
					{ShFlags::Allocate, "Allocate"},
					{ShFlags::Execute, "Execute"}
				};
			}

		public:
			static std::vector<ShFlags> values()
			{
				std::vector<ShFlags> temp;
				for (auto pair : pairs())
				{
					temp.push_back(pair.first);
				}
				return temp;
			}

			static std::string enumName(ShFlags value)
			{
				for (auto pair : pairs())
				{
					if (pair.first == value)
						return pair.second;
				}

				throw std::runtime_error("Enum not found.");
			}

			static int ordinal(ShFlags value)
			{
				std::vector<std::pair<ShFlags, std::string>> temp = pairs();
				for (std::size_t i = 0; i < temp.size(); i++)
				{
					if (temp[i].first == value)
						return i;
				}

				throw std::runtime_error("Enum not found.");
			}

			static ShFlags enumFromString(std::string value)
			{
				for (auto pair : pairs())
				{
					if (pair.second == value)
						return pair.first;
				}

				throw std::runtime_error("Enum not found.");
			}
		};


	public:
		enum class ShType
		{
			NULL = 0x00000000,
			PROGBITS = 0x00000001,
			SYMTAB = 0x00000002,
			STRTAB = 0x00000003,
			RELA = 0x00000004,
			HASH = 0x00000005,
			DYNAMIC = 0x00000006,
			NOTE = 0x00000007,
			NOBITS = 0x00000008,
			REL = 0x00000009,
			SHLIB = 0x0000000a,
			DYNSYM = 0x0000000b,
			PRXREL = 0x700000A0

//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//			private int value;
//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//			private ShType(int val)
	//		{
	//			value=val;
	//		}
//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//			public int getValue()
	//		{
	//			return value;
	//		}
		};

		class ShTypeHelper
		{
		private:
			static std::vector<std::pair<ShType, std::string>> pairs()
			{
				return
				{
					{ShType::NULL, "NULL"},
					{ShType::PROGBITS, "PROGBITS"},
					{ShType::SYMTAB, "SYMTAB"},
					{ShType::STRTAB, "STRTAB"},

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
