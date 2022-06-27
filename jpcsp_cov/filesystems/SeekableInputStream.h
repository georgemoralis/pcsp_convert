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
	class SeekableInputStream : public InputStream, public SeekableDataInput
	{


	public:
		void seek(long long position) = 0; override

		long long length() = 0; override

		int read() = 0; override

		signed char readByte() = 0; override

		short readShort() = 0; override

		int readInt() = 0; override

		int readUnsignedByte() = 0; override

		int readUnsignedShort() = 0; override

		long long readLong() = 0; override

		float readFloat() = 0; override

		double readDouble() = 0; override

		bool readBoolean() = 0; override

		char readChar() = 0; override

		std::string readUTF() = 0; override

		std::string readLine() = 0; override

		void readFully(signed char b[], int off, int len) = 0; override

		void readFully(signed char b[]) = 0; override

		int skipBytes(int bytes) = 0; override

	};

}
