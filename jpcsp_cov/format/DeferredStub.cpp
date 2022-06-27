using namespace std;

#include "DeferredStub.h"

namespace jpcsp::format
{

	DeferredStub::DeferredStub(const string &moduleName, int importAddress, int nid)
	{
		this->moduleName = moduleName;
		this->importAddress = importAddress;
		this->nid = nid;
	}

	string DeferredStub::getModuleName()
	{
		return moduleName;
	}

	int DeferredStub::getImportAddress()
	{
		return importAddress;
	}

	int DeferredStub::getNid()
	{
		return nid;
	}
}
