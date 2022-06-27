using namespace std;

#include "FunctionLibrary.h"

namespace jpcsp::format
{

	Module::Module(const string &name) : m_name(string(name))
	{
		m_functions = unordered_map<string, string>();
	}

	string Module::getName()
	{
		return m_name;
	}

	string Module::getFunctionFromModule(const string &nid)
	{
		try
		{
			return m_functions[nid];
		}
		catch (const NullPointerException &dummy)
		{
			return "";
		}
	}

	int Module::countFunctions()
	{
		return m_functions.size();
	}

	void Module::addFunction(const string &nid, const string &name)
	{
		m_functions.emplace(nid, name);
	}

	string FunctionLibrary::getFunctionFromLibrary(const string &library, const string &nid)
	{
		string ret;
		try
		{
			ret = (m_moduleTable[library])->getFunctionFromModule(nid);
			return ret;
		}
		catch (const NullPointerException &dummy1)
		{
			try
			{
				Module *that = m_moduleTable[library];
				ret = library + "_Unknown_" + nid.substr(2);
				addFunctionToLibrary(library, nid, ret);
				return ret;
			}
			catch (const NullPointerException &dummy2)
			{
				ret = "";
				addModule(library);
				addFunctionToLibrary(library, nid, library + "_Unknown_" + nid.substr(2));
				return ret;
			}
		}
	}

	void FunctionLibrary::addModule(const string &module)
	{
		Module tempVar(module);
		m_moduleTable.emplace(module, &tempVar);
		m_moduleCount++;
	}

	void FunctionLibrary::addFunctionToLibrary(const string &module, const string &nid, const string &name)
	{
		Module *that = m_moduleTable[module];
		that->addFunction(nid, name);
		m_functionCount++;
	}

	int FunctionLibrary::getModuleCount()
	{
		return m_moduleCount;
	}

	int FunctionLibrary::getFunctionCount()
	{
		return m_functionCount;
	}

	FunctionLibrary::FunctionLibrary(const string &fw)
	{
		/*
		m_moduleTable = new Hashtable();
		
		SAXBuilder builder = new SAXBuilder();
		Document doc = builder.build(new File(fw + "/psplibdoc.xml"));
		
		XPath modules = XPath.newInstance("/PSPLIBDOC/PRXFILES/PRXFILE/LIBRARIES/LIBRARY");
		
		List LibList = modules.selectNodes(doc);
		m_moduleList = modules.selectNodes(doc, "//NAME");
		
		Iterator i = LibList.iterator();
		
		int x = 0;
		
		while (i.hasNext()) {
		Element curEl = (Element) i.next();
		String modName = curEl.getChild("NAME").getText();
		Module newMod = new Module(modName);
		List FunctionList = curEl.getChild("FUNCTIONS").getChildren("FUNCTION");
		Iterator j = FunctionList.iterator();
		while (j.hasNext()) {
		Element funcEl = (Element) j.next();
		newMod.addFunction(funcEl.getChild("NID").getText(), funcEl.getChild("NAME").getText());
		m_functionCount++;
		}
		m_moduleCount++;
		m_moduleTable.put(modName, newMod);
		}
		 */
	}
}
