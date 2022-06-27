using namespace std;

#include "Iso9660Handler.h"

namespace jpcsp::filesystems::umdiso::iso9660
{
	using namespace jpcsp::filesystems::umdiso;

	Iso9660Handler::Iso9660Handler(UmdIsoReader *r) : Iso9660Directory(r, 0, 0)
	{

		signed char *sector = r->readSector(16);
		ByteArrayInputStream *byteStream = new ByteArrayInputStream(sector);

		byteStream->skip(157); // reach rootDirTocHeader

		signed char *b = new signed char[38];

		byteStream->read(b);
		Iso9660File *rootDirEntry = new Iso9660File(b,b->length);

		int rootLBA = rootDirEntry->getLBA();
		int rootSize = rootDirEntry->getSize();

		internalDir = new Iso9660Directory(r, rootLBA, rootSize);

		delete rootDirEntry;
		delete byteStream;
	}

	Iso9660File *Iso9660Handler::getEntryByIndex(int index)
	{
		return internalDir->getEntryByIndex(index);
	}

	int Iso9660Handler::getFileIndex(const string &fileName)
	{
		return internalDir->getFileIndex(fileName);
	}
}
