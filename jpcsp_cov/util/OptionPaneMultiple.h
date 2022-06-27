#pragma once

#include <string>
#include <iostream>
#include <any>

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
namespace jpcsp::util
{

	/**
	 *
	 * @author nickblame
	 */
	using Component = java::awt::Component;

	class OptionPaneMultiple
	{
	public:
		JTextField *startaddr;
		JTextField *endaddr;
		JTextField *filename;
//JAVA TO C++ CONVERTER NOTE: Field name conflicts with a method name of the current type:
		bool completed_Conflict = false;
		virtual ~OptionPaneMultiple()
		{
			delete startaddr;
			delete endaddr;
			delete filename;
		}

		OptionPaneMultiple(Component *parentComponent, const std::string &start, const std::string &end);
		virtual std::string *getInput();
		virtual bool completed();

	};

}
