#pragma once

#include "Processor.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <optional>
#include "stringbuilder.h"

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

	using Method = java::lang::reflect::Method;

	using ClassPool = javassist::ClassPool;

	/**
	 *
	 * @author hli, guillaume.serre@gmail.com
	 */
	class AllegrexBasicBlock
	{

	protected:
		int entry = 0;
		int size = 0;
		StringBuilder *buffer = new StringBuilder();
		bool freezed = false;
		static ClassPool *pool;
		Method *method = nullptr;
		long long creationTimestamp = 0;
		Processor *processor = nullptr;
		int executionCount = 1;
		std::optional<int> branchTrue;
		std::optional<int> branchFalse;

	public:
		virtual ~AllegrexBasicBlock()
		{
			delete buffer;
			delete method;
			delete processor;
		}

		int getEntry();

		int getSize();

		AllegrexBasicBlock(Processor *processor, int entry);

		virtual void emit(const std::string &javaCode);

		virtual void freeze();

		virtual void execute();
	};

}
