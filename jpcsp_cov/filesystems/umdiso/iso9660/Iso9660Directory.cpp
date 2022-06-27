using namespace std;

#include "Iso9660Directory.h"
#include "../UmdIsoFile.h"

namespace jpcsp::filesystems::umdiso::iso9660
{
	using Vector = java::util::Vector;
	using namespace jpcsp::filesystems::umdiso;

	Iso9660Directory::Iso9660Directory(UmdIsoReader *r, int directorySector, int directorySize)
	{
		// parse directory sector
		UmdIsoFile *dataStream = new UmdIsoFile(r, directorySector, directorySize);

		files = vector<Iso9660File*>();

		signed char *b;

		int currentPos = 0;

		while (directorySize > 0)
		{
			int entryLength = dataStream->read();

			if (entryLength == 0)
			{
				break;
			}

			directorySize -= entryLength;

			b = new signed char[entryLength - 1];
			dataStream->read(b);

			Iso9660File *file = new Iso9660File(b,b->length);
			files.push_back(file);

//JAVA TO C++ CONVERTER TODO TASK: A 'delete file' statement was not added since file was passed to a method or constructor. Handle memory management manually.
		}

		delete dataStream;
	}

	Iso9660File *Iso9660Directory::getEntryByIndex(int index)
	{
		return files[index];
	}

	int Iso9660Directory::getFileIndex(const string &fileName)
	{
		for (int i = 0;i < files.size();i++)
		{
			string file = files[i]->getFileName();
//JAVA TO C++ CONVERTER TODO TASK: The following Java case-insensitive String method call is not converted:
			if (file.compareToIgnoreCase(fileName) == 0)
			{
				return i;
			}
		}

		throw FileNotFoundException("File " + fileName + " not found in directory.");
	}
}
