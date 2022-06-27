#pragma once

#include "Controller.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <optional>
#include "exceptionhelper.h"

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

	using Point = java::awt::Point;
	using HashMap = java::util::HashMap;

	using ParserConfigurationException = javax::xml::parsers::ParserConfigurationException;

	using keyCode = jpcsp::Controller::keyCode;

	using Document = org::w3c::dom::Document;

	/**
	*
	* @author spip2001
	*/
	class Settings
	{

   private:
	   static const std::string SETTINGS_FILE_NAME;
	   static const std::string DEFAULT_SETTINGS_FILE_NAME;

		static Settings *instance;

		Document *doc;

	public:
		virtual ~Settings()
		{
			delete doc;
		}

		static Settings *get_instance();

		virtual void NullSettings();

		/**
		 * Reads a setting from the xml file and
		 * returns it as a string.
		 * @param path Path of the wanted value
		 * @return
		 */
	private:
		std::string readXmlSetting(const std::string &path);

		/**
		 * Gets the xml document containing settings
		 * @return
		 * @throws ParserConfigurationException 
		 * @throws ParserConfigurationException
		 * @throws IOException
		 * @throws SAXException
		 */
		Document *getSettingsDocument();

		/**
		 * Write settings in file
		 * @param doc Settings as XML document
		 */
		void writeSettings();

	public:
		virtual int *readWindowPos(const std::string &windowname);

	   virtual int *readWindowSize(const std::string &windowname);

		virtual void writeWindowPos(const std::string &windowname, Point *pos);

	   virtual void writeWindowSize(const std::string &windowname, std::string dimension[]);

		virtual bool readBoolOptions(const std::string &option);

		virtual void writeBoolOptions(const std::string &option, bool value);
		virtual std::string readStringOptions(const std::string &option);
			virtual void writeStringOptions(const std::string &option, const std::string &value);
		virtual std::unordered_map<int, keyCode> loadKeys();

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") public void writeKeys(java.util.HashMap<int, jpcsp.Controller.keyCode> keys)
		virtual void writeKeys(std::unordered_map<int, keyCode> &keys);

	private:
		int readKeyOption(const std::string &keyName);

	public:
		virtual void writeKeyOption(const std::string &keyName, int key);

	};

}
