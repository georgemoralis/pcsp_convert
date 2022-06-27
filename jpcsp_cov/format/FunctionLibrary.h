#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "exceptionhelper.h"

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
namespace jpcsp::format
{


	/**
	 *
	 * @author hli
	 */
	class Module
	{

	private:
		const std::string m_name;
		std::unordered_map<std::string, std::string> m_functions;

	public:
		Module(const std::string &name);

		virtual std::string getName();

		virtual std::string getFunctionFromModule(const std::string &nid);

		virtual int countFunctions();

		virtual void addFunction(const std::string &nid, const std::string &name);
	};

	class FunctionLibrary
	{

	private:
		int m_moduleCount = 0;
		int m_functionCount = 0;
		std::unordered_map<std::string, Module*> m_moduleTable;
		std::vector<Module*> m_moduleList;

	public:
		virtual std::string getFunctionFromLibrary(const std::string &library, const std::string &nid);

		virtual void addModule(const std::string &module);

		virtual void addFunctionToLibrary(const std::string &module, const std::string &nid, const std::string &name);

		virtual int getModuleCount();

		virtual int getFunctionCount();

		FunctionLibrary(const std::string &fw);
	};


}
