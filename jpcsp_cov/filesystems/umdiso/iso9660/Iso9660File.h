#pragma once

#include <string>
#include "exceptionhelper.h"

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

namespace jpcsp::filesystems::umdiso::iso9660
{


	/**
	 *
	 * @author gigaherz
	 */
	class Iso9660File
	{

	private:
		int fileLBA = 0;
		int fileSize = 0;
		int fileProperties = 0;
		// padding: byte[3]
		std::string fileName; //[128+1];
		//Iso9660Date date; // byte[7]

		int Ubyte(signed char b);

	public:
		Iso9660File(signed char data[], int length);

		virtual int getLBA();

		virtual int getSize();

		virtual int getProperties();

		virtual std::string getFileName();
	};

}
