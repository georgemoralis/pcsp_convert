using namespace std;

#include "SeekableRandomFile.h"

namespace jpcsp::filesystems
{

	SeekableRandomFile::SeekableRandomFile(const string &fileName, const string &mode) : RandomAccessFile(fileName, mode)
	{
	}

	SeekableRandomFile::SeekableRandomFile(File *name, const string &mode) : RandomAccessFile(name, mode)
	{
	}
}
