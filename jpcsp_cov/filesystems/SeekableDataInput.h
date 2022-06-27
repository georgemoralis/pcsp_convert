#pragma once

#include "Seekable.h"

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
	class SeekableDataInput : public DataInput, public Seekable, public Closeable
	{

	};

}
