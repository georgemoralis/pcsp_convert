using namespace std;

#include "PSF.h"
#include "../util/Utilities.h"

namespace jpcsp::format
{
	using IOException = java::io::IOException;
	using Array = java::lang::reflect::Array;
	using ByteBuffer = java::nio::ByteBuffer;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;

	PSF::PSF(long long p_offset_param_sfo)
	{
		this->p_offset_param_sfo = p_offset_param_sfo;
	}

	void PSF::read(ByteBuffer *f)
	{
		fileidentify = Utilities::readUWord(f);
		if (psfident != fileidentify)
		{
		  cout << "not current psf file!" << endl;
		  return;
		}
		psfversion = Utilities::readUWord(f);
		offsetkeytable = Utilities::readUWord(f);
		offsetvaluetable = Utilities::readUWord(f);
		numberofkeypairs = Utilities::readUWord(f);

		offset_keyname = new int[static_cast<int>(numberofkeypairs)];
		alignment = new signed char[static_cast<int>(numberofkeypairs)];
		datatype = new signed char[static_cast<int>(numberofkeypairs)];
		value_size = new long long[static_cast<int>(numberofkeypairs)];
		value_size_padding = new long long[static_cast<int>(numberofkeypairs)];
		offset_data_value = new long long[static_cast<int>(numberofkeypairs)];

		/*System.out.println(psfversion);
		System.out.println(offsetkeytable);
		System.out.println(offsetvaluetable);
		System.out.println(numberofkeypairs);*/
		for (int i = 0; i < numberofkeypairs; i++)
		{
			offset_keyname[i] = Utilities::readUHalf(f);
			alignment[i] = static_cast<signed char>(Utilities::readUByte(f));
			datatype[i] = static_cast<signed char>(Utilities::readUByte(f));
			value_size[i] = Utilities::readUWord(f);
			value_size_padding[i] = Utilities::readUWord(f);
			offset_data_value[i] = Utilities::readUWord(f);
		  /* System.out.println(offset_keyname[i]);
		   System.out.println(alignment[i]);
		   System.out.println(datatype[i]);
		   System.out.println(value_size[i]);
		   System.out.println(value_size_padding[i]);
		   System.out.println(offset_data_value[i]);*/

		}
		string Key;
		for (int i = 0; i < numberofkeypairs; i++)
		{
			f->position(static_cast<int>(p_offset_param_sfo + offsetkeytable + offset_keyname[i]));
		   Key = Utilities::readStringZ(f);
		   if (datatype[i] == 2)
		   {
			  // String may not be in english!
			  f->position(static_cast<int>(p_offset_param_sfo + offsetvaluetable + offset_data_value[i]));
			  string value = Utilities::readStringZ(f);
			  map.emplace(Key, value);
			  //System.out.println(Key + " string = " + value);
		   }
		   else if (datatype[i] == 4)
		   {
			  f->position(static_cast<int>(p_offset_param_sfo + offsetvaluetable + offset_data_value[i]));
			  long long value = Utilities::readUWord(f);
			  map.emplace(Key, value);
			  //System.out.println(Key + " int = "  + value);
		   }
		   else if (datatype[i] == 0)
		   {
			   f->position(static_cast<int>(p_offset_param_sfo + offsetvaluetable + offset_data_value[i]));
			   signed char *value = new signed char[static_cast<int>(value_size[i])];
			   f->get(value);
			   map.emplace(Key, value);
			   //System.out.println(Key + " = <binary data>");
		   }
		   else
		   {
			   cout << Key << " UNIMPLEMENT DATATYPE " << datatype[i] << endl;
		   }
		}
	}

	string PSF::toString()
	{
		StringBuilder *sb = new StringBuilder();
		for (auto entry : map)
		{
			sb->append(entry.first)->append(" = ");
			if (dynamic_cast<Array*>(entry.second) != nullptr)
			{
				sb->append("<binary data>");
			}
			else
			{
				sb->append(entry.second);
			}
			sb->append('\n');
		}

		delete sb;
		return sb->toString();
	}

	any PSF::get(const string &key)
	{
		return map[key];
	}

	string PSF::getString(const string &key)
	{
		return any_cast<string>(map[key]);
	}

	long long PSF::getNumeric(const string &key)
	{
		return any_cast<optional<long long>>(map[key]);
	}
}
