using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "PBP.h"
#include "../util/Utilities.h"

namespace jpcsp::format
{
	using File = java::io::File;
	using FileOutputStream = java::io::FileOutputStream;
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using namespace jpcsp::filesystems;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;
const string PBP::PBP_UNPACK_PATH_PREFIX = "unpacked-pbp/";

	bool PBP::isValid()
	{
		return ((p_magic & 0xFFFFFFFFLL) == PBP_MAGIC);
	}

	void PBP::setElf32(Elf32 *elf)
	{
		elf32 = elf;
	}

	Elf32 *PBP::getElf32()
	{
		return elf32;
	}

	void PBP::setInfo(const string &msg)
	{
		info = msg;
	}

	string PBP::getInfo()
	{
		return info;
	}

	PBP::PBP(ByteBuffer *f)
	{
		size_pbp = static_cast<int>(f->capacity());
		p_magic = Utilities::readUWord(f);
		if (isValid())
		{
			p_version = Utilities::readUWord(f);
			p_offset_param_sfo = Utilities::readUWord(f);
			p_offset_icon0_png = Utilities::readUWord(f);
			p_offset_icon1_pmf = Utilities::readUWord(f);
			p_offset_pic0_png = Utilities::readUWord(f);
			p_offset_pic1_png = Utilities::readUWord(f);
			p_offset_snd0_at3 = Utilities::readUWord(f);
			p_offset_psp_data = Utilities::readUWord(f);
			p_offset_psar_data = Utilities::readUWord(f);

			size_param_sfo = static_cast<int>(p_offset_icon0_png - p_offset_param_sfo);
			size_icon0_png = static_cast<int>(p_offset_icon1_pmf - p_offset_icon0_png);
			size_icon1_pmf = static_cast<int>(p_offset_pic0_png - p_offset_icon1_pmf);
			size_pic0_png = static_cast<int>(p_offset_pic1_png - p_offset_pic0_png);
			size_pic1_png = static_cast<int>(p_offset_snd0_at3 - p_offset_pic1_png);
			size_snd0_at3 = static_cast<int>(p_offset_psp_data - p_offset_snd0_at3);
			size_psp_data = static_cast<int>(p_offset_psar_data - p_offset_psp_data);
			size_psar_data = static_cast<int>(size_pbp - p_offset_psar_data);

//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
			info = this->toString();
		}
	}

	PSF *PBP::readPSF(ByteBuffer *f)
	{
		if (p_offset_param_sfo > 0)
		{
		   f->position(static_cast<int>(p_offset_param_sfo));
		   PSF *psf1 = new PSF(p_offset_param_sfo);
		   psf1->read(f);

//JAVA TO C++ CONVERTER TODO TASK: A 'delete psf1' statement was not added since psf1 was used in a 'return' or 'throw' statement.
		   return psf1;
		}
		return nullptr;
	}

	string PBP::toString()
	{
		StringBuilder *str = new StringBuilder();
		str->append("-----PBP HEADER---------" + "\n");
		str->append("p_magic " + "\t\t" + Utilities::formatString("long", Long::toHexString(p_magic & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_version " + "\t\t" + Utilities::formatString("long", Long::toHexString(p_version & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_offset_param_sfo " + "\t" + Utilities::formatString("long", Long::toHexString(p_offset_param_sfo & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_offset_icon0_png " + "\t" + Utilities::formatString("long", Long::toHexString(p_offset_icon0_png & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_offset_icon1_pmf " + "\t" + Utilities::formatString("long", Long::toHexString(p_offset_icon1_pmf & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_offset_pic0_png " + "\t" + Utilities::formatString("long", Long::toHexString(p_offset_pic0_png & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_offset_pic1_png " + "\t" + Utilities::formatString("long", Long::toHexString(p_offset_pic1_png & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_offset_snd0_at3 " + "\t" + Utilities::formatString("long", Long::toHexString(p_offset_snd0_at3 & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_offset_psp_data " + "\t" + Utilities::formatString("long", Long::toHexString(p_offset_psp_data & 0xFFFFFFFFLL)->toUpperCase()) + "\n");
		str->append("p_offset_psar_data " + "\t" + Utilities::formatString("long", Long::toHexString(p_offset_psar_data & 0xFFFFFFFFLL)->toUpperCase()) + "\n");

		delete str;
		return str->toString();
	}

	long long PBP::getMagic()
	{
		return p_magic;
	}

	long long PBP::getVersion()
	{
		return p_version;
	}

	long long PBP::getOffsetParam()
	{
		return p_offset_param_sfo;
	}

	long long PBP::getOffsetIcon0()
	{
		return p_offset_icon0_png;
	}

	long long PBP::getOffsetIcon1()
	{
		return p_offset_icon1_pmf;
	}

	long long PBP::getOffsetPic0()
	{
		return p_offset_pic0_png;
	}

	long long PBP::getOffsetPic1()
	{
		return p_offset_pic1_png;
	}

	long long PBP::getOffsetSnd0()
	{
		return p_offset_snd0_at3;
	}

	long long PBP::getOffsetPspData()
	{
		return p_offset_psp_data;
	}

	long long PBP::getOffsetPsarData()
	{
		return p_offset_psar_data;
	}

	int PBP::getSizeIcon0()
	{
		return size_icon0_png;
	}

	bool PBP::deleteDir(File *dir)
	{
		if (dir->isDirectory())
		{
			string *children = dir->list();
			for (int i = 0; i < children->length; i++)
			{
				File tempVar(dir, children[i]);
				bool success = deleteDir(&tempVar);
				if (!success)
				{
					return false;
				}
			}
		}
		// The directory is now empty so delete it
		return dir->delete();
	}

	void PBP::unpackPBP(ByteBuffer *f)
	{
		f->position(0); //seek to 0
		PBP *pbp = new PBP(f);
		if (!pbp->isValid())
		{
			delete pbp;
			return;
		}
		File *dir = new File(PBP_UNPACK_PATH_PREFIX);

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
