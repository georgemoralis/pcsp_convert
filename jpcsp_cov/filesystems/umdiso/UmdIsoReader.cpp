using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "UmdIsoReader.h"
#include "iso9660/Iso9660Directory.h"
#include "iso9660/Iso9660Handler.h"
#include "iso9660/Iso9660File.h"

namespace jpcsp::filesystems::umdiso
{
	using namespace jpcsp::filesystems::umdiso::iso9660;
	using namespace org::bolet::jgz;

	int UmdIsoReader::Ubyte(signed char b)
	{
		return (static_cast<int>(b)) & 255;
	}

	int UmdIsoReader::BytesToInt(signed char bytes[], int offset)
	{
		return Ubyte(bytes[offset + 0]) | (Ubyte(bytes[offset + 1]) << 8) | (Ubyte(bytes[offset + 2]) << 16) | (bytes[offset + 3] << 24);
	}

	UmdIsoReader::UmdIsoReader(const string &umdFilename)
	{
		fileName = umdFilename;
		fileReader = new RandomAccessFile(umdFilename,"r");

		/*
		    u32 'CISO'
		    u32 0?
		    u32 image size in bytes (why? it could have been sectors and make thigns simpler!)
		    u32 sector size? (00000800 = 2048 = sector size)
		    u32 ? (1)
		    u32[] sector offsets (as many as image size / sector size, I guess)
		*/

		format = FileFormat::Uncompressed;
		numSectors = static_cast<int>(fileReader->length() / 2048);

		signed char *id = new signed char[24];

		fileReader->seek(0);
		fileReader->read(id);

		if (((static_cast<char>(id[0])) == 'C') && ((static_cast<char>(id[1])) == 'I') && ((static_cast<char>(id[2])) == 'S') && ((static_cast<char>(id[3])) == 'O'))
		{
			format = FileFormat::CompressedCSO;

			int lenInbytes = BytesToInt(id,8);
			int sectorSize = BytesToInt(id,16);

			//int version = Ubyte(id[20]);
			offsetShift = Ubyte(id[21]);

			numSectors = lenInbytes / sectorSize;

			sectorOffsets = new long long[numSectors + 1];

			signed char *offsetData = new signed char[(numSectors + 1) * 4];

			fileReader->read(offsetData);

			for (int i = 0;i <= numSectors;i++)
			{
				sectorOffsets[i] = (static_cast<long long>(BytesToInt(offsetData, i * 4))) & 0xFFFFFFFFLL;
				if (i > 0)
				{
					if ((sectorOffsets[i] & 0x7FFFFFFF) < (sectorOffsets[i - 1] & 0x7FFFFFFF))
					{
						throw IOException("Invalid offset [" + to_string(i) + "]: " + to_string(sectorOffsets[i]) + "<" + to_string(sectorOffsets[i - 1]));
					}
				}
			}
		}

		// when we reach here, we assume it's either a .ISO or a .CSO
		// but we still need to make sure of that

		id = new signed char[6];

		UmdIsoFile *f = new UmdIsoFile(this, 16, 2048);
		f->read(id);

		if (((static_cast<char>(id[1])) == 'C') && ((static_cast<char>(id[2])) == 'D') && ((static_cast<char>(id[3])) == '0') && ((static_cast<char>(id[4])) == '0') && ((static_cast<char>(id[5])) == '1'))
		{
			if (format == FileFormat::Uncompressed)
			{
				numSectors = static_cast<int>(fileReader->length() / 2048);
			}

			delete f;
			return;
		}

		format = FileFormat::Unknown;

		delete f;
		throw IOException("Unsupported file format or corrupt file.");
	}

	signed char *UmdIsoReader::readSector(int sectorNumber)
	{
		if ((sectorNumber < 0) || (sectorNumber >= numSectors))
		{
			throw out_of_range("Sector number " + to_string(sectorNumber) + " out of bounds.");
		}

		if (format == FileFormat::Uncompressed)
		{
			signed char *bytes = new signed char[2048];

			fileReader->seek(2048 * sectorNumber);
			fileReader->read(bytes);
			return bytes;
		}

		if (format == FileFormat::CompressedCSO)
		{
			long long sectorOffset = sectorOffsets[sectorNumber];
			long long sectorEnd = sectorOffsets[sectorNumber + 1];

			if ((sectorOffset & 0x80000000) != 0)
			{
				long long realOffset = (sectorOffset & 0x7fffffff) << offsetShift;

				signed char *bytes = new signed char[2048];

				fileReader->seek(realOffset);
				fileReader->read(bytes);
				return bytes;
			}

			sectorEnd = (sectorEnd & 0x7fffffff) << offsetShift;
			sectorOffset = (sectorOffset & 0x7fffffff) << offsetShift;

			int compressedLength = static_cast<int>(sectorEnd - sectorOffset);
			if (compressedLength < 0)
			{
				return new signed char[2048];
			}

			signed char *compressedData = new signed char[compressedLength];

			fileReader->seek(sectorOffset);
			fileReader->read(compressedData);

			signed char *data = new signed char[2048];

			try
			{
				Inflater *inf = new Inflater();

				ByteArrayInputStream *b = new ByteArrayInputStream(compressedData);
				inf->reset(b);
				//inf.setRawStream(b);
				inf->readAll(data,0,data->length);

//JAVA TO C++ CONVERTER TODO TASK: A 'delete b' statement was not added since b was passed to a method or constructor. Handle memory management manually.
				delete inf;
			}
			catch (const IOException &e)
			{
				System::err::print("Exception while uncompressing sector from " + fileName);
				e->printStackTrace();
			}

			return data;
		}

		throw IOException("Unsupported file format or corrupt file.");
	}

	UmdIsoFile *UmdIsoReader::getFile(const string &filePath)
	{
		Iso9660Directory *dir = new Iso9660Handler(this);

		string *path = filePath.split("[\\/]");

		Iso9660File *info = nullptr;
		// walk through path
		for (int i = 0;i < path->length;)
		{
//JAVA TO C++ CONVERTER TODO TASK: The following Java case-insensitive String method call is not converted:
			if (path[i].compareToIgnoreCase(".") == 0)
			{
				//do nothing
			}
//JAVA TO C++ CONVERTER TODO TASK: The following Java case-insensitive String method call is not converted:
			else if (path[i].compareToIgnoreCase("..") == 0)
			{
				i = max(0,i - 1);
			}
			else
			{
				string pathName = path[i];
				int index = dir->getFileIndex(path[i]);
				info = dir->getEntryByIndex(index);
				dir = nullptr;
				if ((info->getProperties() & 2) == 2) // if it's a directory
				{
					dir = new Iso9660Directory(this, info->getLBA(), info->getSize());
					info = nullptr;
				}
				i++;
			}
		}

		if (info == nullptr)
		{
			delete dir;
			throw FileNotFoundException("File '" + filePath + "' not found or not a file.");
		}

		int fileStart = info->getLBA();
		long long fileLength = info->getSize();

		delete dir;

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
