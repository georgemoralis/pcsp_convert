#pragma once

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
	class Seekable
	{

	public:
		virtual long long length() = 0;

		virtual void seek(long long position) = 0;

		virtual long long getFilePointer() = 0;
	};

}
