using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "UmdIsoFile.h"

namespace jpcsp::filesystems::umdiso
{
	using namespace jpcsp::filesystems;

	UmdIsoFile::UmdIsoFile(UmdIsoReader *reader, int startSector, long long lengthInBytes)
	{
		startSectorNumber = startSector;
		currentSectorNumber = startSectorNumber;
		currentOffset = 0;
		currentSector = reader->readSector(startSector);
		maxOffset = lengthInBytes;
		sectorOffset = 0;
		internalReader = reader;
	}

	int UmdIsoFile::Ubyte(signed char b)
	{
		return (static_cast<int>(b)) & 255;
	}

	int UmdIsoFile::read()
	{
		// I hate Java. Actuall I hate whoever decided to make "byte" signed,
		// and then decided that streams would have a read() function returning a value [0..255], and -1 for EOF

		if (currentOffset == maxOffset)
		{
			return -1; //throw new java.io.EOFException();
		}

		if (sectorOffset == 2048)
		{
			currentSectorNumber++;
			currentSector = internalReader->readSector(currentSectorNumber);
			sectorOffset = 0;
		}
		currentOffset++;

		int debuggingVariable = Ubyte(currentSector[sectorOffset++]); // make unsigned

		assert((debuggingVariable >= 0));

		return debuggingVariable;

	}

	void UmdIsoFile::reset()
	{
		seek(0);
	}

	long long UmdIsoFile::skip(long long n)
	{
		long long oldOffset = currentOffset;
		long long newOffset = currentOffset + n;

		if (n < 0)
		{
			return n;
		}

		if (newOffset >= maxOffset)
		{
			newOffset = maxOffset;
		}

		seek(currentOffset + n);

		return currentOffset - oldOffset;
	}

	long long UmdIsoFile::length()
	{
		return maxOffset;
	}

	void UmdIsoFile::seek(long long offset)
	{
		long long endOffset = offset;

		if (offset < 0)
		{
			throw IOException("Seek offset " + to_string(offset) + " out of bounds.");
		}

		int oldSectorNumber = currentSectorNumber;
		long long newOffset = endOffset;
		int newSectorNumber = startSectorNumber + static_cast<int>(newOffset / 2048);
		if (oldSectorNumber != newSectorNumber)
		{
			currentSector = internalReader->readSector(newSectorNumber);
		}
		currentOffset = newOffset;
		currentSectorNumber = newSectorNumber;
		sectorOffset = static_cast<int>(currentOffset % 2048);
	}

	long long UmdIsoFile::getFilePointer()
	{
		return currentOffset;
	}

	signed char UmdIsoFile::readByte()
	{
		if (currentOffset >= maxOffset)
		{
			throw EOFException();
		}

		return static_cast<signed char>(read());
	}

	short UmdIsoFile::readShort()
	{
		return static_cast<short>(readUnsignedByte() | ((static_cast<int>(readByte())) << 8));
	}

	int UmdIsoFile::readInt()
	{
		return (readUnsignedByte() | ((static_cast<int>(readUnsignedByte())) << 8) | ((static_cast<int>(readUnsignedByte())) << 16) | ((static_cast<int>(readByte())) << 24));
	}

	int UmdIsoFile::readUnsignedByte()
	{
		if (currentOffset >= maxOffset)
		{
			throw EOFException();
		}

		return read();
	}

	int UmdIsoFile::readUnsignedShort()
	{
		return (static_cast<int>(readShort())) & 0xFFFF;
	}

	long long UmdIsoFile::readLong()
	{
		return ((static_cast<long long>(readInt())) & 0xFFFFFFFFLL) | ((static_cast<long long>(readInt())) << 32);
	}

	float UmdIsoFile::readFloat()
	{
		if (currentOffset >= maxOffset)
		{
			throw EOFException();
		}

		DataInputStream *s = new DataInputStream(this);

		delete s;
		return s->readFloat();
	}

	double UmdIsoFile::readDouble()
	{
		if (currentOffset >= maxOffset)
		{
			throw EOFException();
		}

		DataInputStream *s = new DataInputStream(this);

		delete s;
		return s->readDouble();
	}

	bool UmdIsoFile::readBoolean()
	{
		return (readUnsignedByte() != 0);
	}

	char UmdIsoFile::readChar()
	{
		if (currentOffset >= maxOffset)
		{
			throw EOFException();
		}

		DataInputStream *s = new DataInputStream(this);

		delete s;
		return s->readChar();
	}

	string UmdIsoFile::readUTF()
	{
		if (currentOffset >= maxOffset)
		{
			throw EOFException();
		}

		DataInputStream *s = new DataInputStream(this);

		delete s;
		return s->readUTF();
	}

	string UmdIsoFile::readLine()
	{
		if (currentOffset >= maxOffset)
		{
			throw EOFException();
		}

		DataInputStream *s = new DataInputStream(this);

		delete s;
		return s->readLine();
	}

	void UmdIsoFile::readFully(signed char b[], int off, int len)
	{
		if (currentOffset >= maxOffset)
		{

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
