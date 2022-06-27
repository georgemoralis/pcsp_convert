#pragma once

#include "UmdIsoFile.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <utility>
#include "exceptionhelper.h"

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

namespace jpcsp::filesystems::umdiso
{

	using namespace jpcsp::filesystems::umdiso::iso9660;

	//import java.util.zip.*;
	using namespace org::bolet::jgz;

	/**
	 *
	 * @author gigaherz
	 */
	class UmdIsoReader
	{

	public:
		RandomAccessFile *fileReader;

	public:
		enum class FileFormat
		{
			Uncompressed,
			CompressedCSO,
			CompressedDAX, // not implemented yet
			//...
			Unknown
		};

		class FileFormatHelper
		{
		private:
			static std::vector<std::pair<FileFormat, std::string>> pairs()
			{
				return
				{
					{FileFormat::Uncompressed, "Uncompressed"},
					{FileFormat::CompressedCSO, "CompressedCSO"},
					{FileFormat::CompressedDAX, "CompressedDAX"},
					{FileFormat::Unknown, "Unknown"}
				};
			}

		public:
			static std::vector<FileFormat> values()
			{
				std::vector<FileFormat> temp;
				for (auto pair : pairs())
				{
					temp.push_back(pair.first);
				}
				return temp;
			}

			static std::string enumName(FileFormat value)
			{
				for (auto pair : pairs())
				{
					if (pair.first == value)
						return pair.second;
				}

				throw std::runtime_error("Enum not found.");
			}

			static int ordinal(FileFormat value)
			{
				std::vector<std::pair<FileFormat, std::string>> temp = pairs();
				for (std::size_t i = 0; i < temp.size(); i++)
				{
					if (temp[i].first == value)
						return i;
				}

				throw std::runtime_error("Enum not found.");
			}

			static FileFormat enumFromString(std::string value)
			{
				for (auto pair : pairs())
				{
					if (pair.second == value)
						return pair.first;
				}

				throw std::runtime_error("Enum not found.");
			}
		};


	public:
		FileFormat format = static_cast<FileFormat>(0);

		int numSectors = 0;
		long long *sectorOffsets; // for CSO/DAX

		int offsetShift = 0; // for CSO

		std::string fileName;

		virtual ~UmdIsoReader()
		{
			delete fileReader;
			delete[] sectorOffsets;
		}

	private:
		int Ubyte(signed char b);

		int BytesToInt(signed char bytes[], int offset);

	public:
		UmdIsoReader(const std::string &umdFilename);

		virtual signed char *readSector(int sectorNumber);

		virtual UmdIsoFile *getFile(const std::string &filePath);

	};

}
