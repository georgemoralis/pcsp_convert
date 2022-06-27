#pragma once

#include "Iso9660Directory.h"
#include "../UmdIsoReader.h"
#include "Iso9660File.h"
#include <string>

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

namespace jpcsp::filesystems::umdiso::iso9660
{

	using namespace jpcsp::filesystems::umdiso;

	/**
	 *
	 * @author gigaherz
	 */
	class Iso9660Handler : public Iso9660Directory
	{

	private:
		Iso9660Directory *internalDir;

	public:
		virtual ~Iso9660Handler()
		{
			delete internalDir;
		}

		Iso9660Handler(UmdIsoReader *r);

		Iso9660File *getEntryByIndex(int index) override;

		int getFileIndex(const std::string &fileName) override;

	};

}
