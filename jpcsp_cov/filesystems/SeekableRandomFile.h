#pragma once

#include "SeekableDataInput.h"
#include <string>

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

namespace jpcsp::filesystems
{


	/**
	 *
	 * @author gigaherz
	 */
	class SeekableRandomFile : public RandomAccessFile, public SeekableDataInput
	{

	public:
		SeekableRandomFile(const std::string &fileName, const std::string &mode);

		SeekableRandomFile(File *name, const std::string &mode);

	};

}
