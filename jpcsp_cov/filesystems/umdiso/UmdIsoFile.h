#pragma once

#include "../SeekableInputStream.h"
#include "UmdIsoReader.h"
#include <string>
#include "exceptionhelper.h"
#include <cassert>

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

namespace jpcsp::filesystems::umdiso
{

	using namespace jpcsp::filesystems;

	/**
	 *
	 * @author gigaherz
	 */
	class UmdIsoFile : public SeekableInputStream
	{

	private:
		int startSectorNumber = 0;
		int currentSectorNumber = 0;
		long long currentOffset = 0;
		long long maxOffset = 0;

		signed char *currentSector;
		int sectorOffset = 0;

	public:
		UmdIsoReader *internalReader;

		virtual ~UmdIsoFile()
		{
			delete[] currentSector;
			delete internalReader;
		}

		UmdIsoFile(UmdIsoReader *reader, int startSector, long long lengthInBytes);

	private:
		int Ubyte(signed char b);

	public:
		int read() override;

		void reset() override;

		long long skip(long long n) override;

		long long length() override;

		void seek(long long offset) override;

		long long getFilePointer() override;


		signed char readByte() override;

		short readShort() override;

		int readInt() override;

		int readUnsignedByte() override;

		int readUnsignedShort() override;

		long long readLong() override;

		float readFloat() override;

		double readDouble() override;

		bool readBoolean() override;

		char readChar() override;

		std::string readUTF() override;

		std::string readLine() override;

		void readFully(signed char b[], int off, int len) override;

		void readFully(signed char b[]) override;

		int skipBytes(int bytes) override;

	};

}
