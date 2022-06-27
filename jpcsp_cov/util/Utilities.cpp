using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "Utilities.h"

namespace jpcsp::util
{
	using IOException = java::io::IOException;
	using namespace jpcsp::filesystems;
	using ByteBuffer = java::nio::ByteBuffer;

	string Utilities::formatString(const string &type, const string &oldstring)
	{
		int counter = 0;
		if (type == "byte")
		{
			counter = 2;
		}
		if (type == "short")
		{
			counter = 4;
		}
		if (type == "long")
		{
			counter = 8;
		}
		int len = oldstring.length();
		StringBuilder *sb = new StringBuilder();
		while (len++ < counter)
		{
			sb->append('0');
		}
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
		oldstring = sb->append(oldstring)->toString();

		delete sb;
		return oldstring;

	}

	string Utilities::integerToBin(int value)
	{
		return Long::toBinaryString(0x0000000100000000LL | ((static_cast<long long>(value)) & 0x00000000FFFFFFFFLL))->substr(1);
	}

	string Utilities::integerToHex(int value)
	{
		return Integer::toHexString(0x100 | value)->substr(1).toUpperCase();
	}

	string Utilities::integerToHexShort(int value)
	{
		return Integer::toHexString(0x10000 | value)->substr(1).toUpperCase();
	}

	long long Utilities::readUWord(SeekableDataInput *f)
	{
		long long l = (f->readUnsignedByte() | (f->readUnsignedByte() << 8) | (f->readUnsignedByte() << 16) | (f->readUnsignedByte() << 24));
		return (l & 0xFFFFFFFFLL);
	}

	int Utilities::readUByte(SeekableDataInput *f)
	{
		return f->readUnsignedByte();
	}

	int Utilities::readUHalf(SeekableDataInput *f)
	{
		return f->readUnsignedByte() | (f->readUnsignedByte() << 8);
	}

	int Utilities::readWord(SeekableDataInput *f)
	{
		//readByte() isn't more correct? (already exists one readUWord() method to unsign values)
		return (f->readUnsignedByte() | (f->readUnsignedByte() << 8) | (f->readUnsignedByte() << 16) | (f->readUnsignedByte() << 24));
	}

	void Utilities::readBytesToBuffer(SeekableDataInput *f, ByteBuffer *buf, int offset, int size)
	{
		f->readFully(buf->array(), offset + buf->arrayOffset(), size);
	}

	void Utilities::copyByteBuffertoByteBuffer(ByteBuffer *src, ByteBuffer *dst, int offset, int size)
	{
		signed char *data = new signed char[size];
		src->get(data);
		dst->position(offset);
		dst->put(data);
	}

	string Utilities::readStringZ(SeekableDataInput *f)
	{
		StringBuilder *sb = new StringBuilder();
		int b;
		for (;;)
		{
			b = f->readUnsignedByte();
			if (b == 0)
			{
				break;
			}
			sb->append(static_cast<char>(b));
		}

		delete sb;
		return sb->toString();
	}

	string Utilities::readStringZ(signed char mem[], int offset)
	{
		StringBuilder *sb = new StringBuilder();
		int b;
		for (;;)
		{
			b = mem[offset++];
			if (b == 0)
			{
				break;
			}
			sb->append(static_cast<char>(b));
		}

		delete sb;
		return sb->toString();
	}

	string Utilities::readStringZ(ByteBuffer *buf, int offset)
	{
		StringBuilder *sb = new StringBuilder();
		signed char b;
		for (;;)
		{
			b = buf->get(offset++);
			if (b == 0)
			{
				break;
			}
			sb->append(static_cast<char>(b));
		}

		delete sb;
		return sb->toString();
	}

	string Utilities::readStringZ(ByteBuffer *buf)
	{
		StringBuilder *sb = new StringBuilder();
		signed char b;
		for (;;)
		{
			  b = static_cast<signed char>(readUByte(buf));
			if (b == 0)
			{
				break;
			}
			sb->append(static_cast<char>(b));
		}

		delete sb;
		return sb->toString();
	}

	string Utilities::readStringNZ(ByteBuffer *buf, int offset, int n)
	{
		StringBuilder *sb = new StringBuilder();
		signed char b;
		for (; n > 0; n--)
		{
			b = buf->get(offset++);
			if (b == 0)
			{
				break;
			}
			sb->append(static_cast<char>(b));
		}

		delete sb;
		return sb->toString();
	}

	short Utilities::getUnsignedByte(ByteBuffer *bb)
	{
	   return (static_cast<short>(bb->get() & 0xff));
	}

	short Utilities::readUByte(ByteBuffer *buf)
	{
	  return getUnsignedByte(buf);
	}

	int Utilities::readUHalf(ByteBuffer *buf)
	{
		return getUnsignedByte(buf) | (getUnsignedByte(buf) << 8);
	}

	long long Utilities::readUWord(ByteBuffer *buf)
	{
		long long l = (getUnsignedByte(buf) | (getUnsignedByte(buf) << 8) | (getUnsignedByte(buf) << 16) | (getUnsignedByte(buf) << 24));
		return (l & 0xFFFFFFFFLL);

	}


//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
