#pragma once

#include <string>
#include <unordered_map>
#include <optional>

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
namespace jpcsp
{

	using HashMap = java::util::HashMap;
	using namespace jpcsp;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.Syscallv15.*;

	class NIDMapper
	{
	private:
		static NIDMapper *instance;
//JAVA TO C++ CONVERTER NOTE: Field name conflicts with a method name of the current type:
		std::unordered_map<int, int> nidToSyscall_Conflict;
		std::unordered_map<std::string, std::unordered_map<int, int>> moduleToNidTable;

	public:
		static NIDMapper *get_instance();

		virtual void Initialise();

		/** returns -1 if the nid couldn't be mapped */
		virtual int nidToSyscall(int nid);

		/** @param modulename Example: sceRtc
		 * @param address Address of export (example: start of function). */
		virtual void addModuleNid(const std::string &modulename, int nid, int address);

		/** Use this when unloading modules */
		virtual void removeModuleNids(const std::string &modulename);

		/** returns -1 if the nid couldn't be mapped */
		virtual int moduleNidToAddress(const std::string &modulename, int nid);
	};

}
