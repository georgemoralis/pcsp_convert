using namespace std;

#include "NIDMapper.h"
#include "Syscallv15.h"

namespace jpcsp
{
	using HashMap = java::util::HashMap;
	using FileNotFoundException = java::io::FileNotFoundException;
	using FileReader = java::io::FileReader;
	using BufferedReader = java::io::BufferedReader;
	using namespace jpcsp;
//	import static jpcsp.Syscallv15.*;
NIDMapper *NIDMapper::instance;

	NIDMapper *NIDMapper::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new NIDMapper();
		}
		return instance;
	}

	void NIDMapper::Initialise()
	{
		moduleToNidTable = unordered_map<string, unordered_map<int, int>>();
	   nidToSyscall_Conflict = unordered_map<int, int>();
		for (int i = 0; i < Syscallv15::syscalls->length; i++)
		{
			   int syscall = Syscallv15::syscalls[i][0];
			   long long nid = Syscallv15::syscalls[i][1];
				nidToSyscall_Conflict.emplace(static_cast<int>(nid),syscall);
		}
	}

	int NIDMapper::nidToSyscall(int nid)
	{
		optional<int> code = nidToSyscall_Conflict[nid];
		if (!code)
		{
			return -1;
		}
		return code.value();
	}

	void NIDMapper::addModuleNid(const string &modulename, int nid, int address)
	{
		unordered_map<int, int> nidToAddress;

		nidToAddress = moduleToNidTable[modulename];
		if (nidToAddress.empty())
		{
			nidToAddress = unordered_map<int, int>();
			moduleToNidTable.emplace(modulename, nidToAddress);
		}

		nidToAddress.emplace(nid, address);
	}

	void NIDMapper::removeModuleNids(const string &modulename)
	{
		moduleToNidTable.erase(modulename);
	}

	int NIDMapper::moduleNidToAddress(const string &modulename, int nid)
	{
		unordered_map<int, int> nidToAddress;
		optional<int> address;

		nidToAddress = moduleToNidTable[modulename];
		if (nidToAddress.empty())
		{
			// module is not loaded
			return -1;
		}

		address = nidToAddress[nid];
		if (!address)
		{
			// nid is not recognized
			return -1;
		}

		return address.value();
	}
}
