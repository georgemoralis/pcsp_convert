using namespace std;

#include "Iso9660File.h"

namespace jpcsp::filesystems::umdiso::iso9660
{

	int Iso9660File::Ubyte(signed char b)
	{
		return (static_cast<int>(b)) & 255;
	}

	Iso9660File::Iso9660File(signed char data[], int length)
	{

		/*
		 -- 1           Length of Directory Record (LEN-DR) -- read by the Iso9660Directory
		2           Extended Attribute Record Length
		3 to 10     Location of Extent
		11 to 18    Data Length
		19 to 25    Recording Date and Time
		26          File Flags
		27          File Unit Size
		28          Interleave Gap Size
		29 to 32    Volume Sequence Number
		33          Length of File Identifier (LEN_FI)
		34 to (33+LEN_FI)   File Identifier
		(34 + LEN_FI)   Padding Field
		
		*/        

		fileLBA = Ubyte(data[1]) | (Ubyte(data[2]) << 8) | (Ubyte(data[3]) << 16) | (data[4] << 24);
		fileSize = Ubyte(data[9]) | (Ubyte(data[10]) << 8) | (Ubyte(data[11]) << 16) | (data[12] << 24);
		fileProperties = data[24];

		if ((fileLBA < 0) || (fileSize < 0))
		{
			throw IOException("WTF?! Size or lba < 0?!");
		}

		int fileNameLength = data[31];

		fileName = "";
		for (int i = 0;i < fileNameLength;i++)
		{
			char c = static_cast<char>(data[32 + i]);
			if (c == 0)
			{
				c = '.';
			}

			fileName += c;
		}

	}

	int Iso9660File::getLBA()
	{
		return fileLBA;
	}

	int Iso9660File::getSize()
	{
		return fileSize;
	}

	int Iso9660File::getProperties()
	{
		return fileProperties;
	}

	string Iso9660File::getFileName()
	{
		return fileName;
	}
}
