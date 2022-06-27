#pragma once

#include "Iso9660File.h"
#include "../UmdIsoReader.h"
#include <string>
#include <vector>
#include "exceptionhelper.h"

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

namespace jpcsp::filesystems::umdiso::iso9660
{

	using Vector = java::util::Vector;
	using namespace jpcsp::filesystems::umdiso;

	/**
	 *
	 * @author gigaherz
	 */
	class Iso9660Directory
	{

	private:
		std::vector<Iso9660File*> files;

	public:
		Iso9660Directory(UmdIsoReader *r, int directorySector, int directorySize);

		virtual Iso9660File *getEntryByIndex(int index);

		virtual int getFileIndex(const std::string &fileName);

	};

}
