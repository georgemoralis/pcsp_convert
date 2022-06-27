using namespace std;

#include "ScePspDateTime.h"

namespace jpcsp::HLE
{
	using Calendar = java::util::Calendar;
	using Date = java::util::Date;
	using Memory = jpcsp::Memory;

	ScePspDateTime::ScePspDateTime(long long time)
	{
		Calendar *cal = Calendar::getInstance();
		Date date = Date(time);
		cal->setTime(date);

		this->year = cal->get(Calendar::YEAR);
		this->month = 1 + cal->get(Calendar::MONTH); // check
		this->day = cal->get(Calendar::DAY_OF_MONTH);
		this->hour = cal->get(Calendar::HOUR);
		this->minute = cal->get(Calendar::MINUTE);
		this->second = cal->get(Calendar::SECOND);
		this->microsecond = cal->get(Calendar::MILLISECOND);
	}

	ScePspDateTime::ScePspDateTime()
	{
		Calendar *cal = Calendar::getInstance();

		this->year = cal->get(Calendar::YEAR);
		this->month = 1 + cal->get(Calendar::MONTH); // check
		this->day = cal->get(Calendar::DAY_OF_MONTH);
		this->hour = cal->get(Calendar::HOUR);
		this->minute = cal->get(Calendar::MINUTE);
		this->second = cal->get(Calendar::SECOND);
		this->microsecond = cal->get(Calendar::MILLISECOND);
	}

	ScePspDateTime::ScePspDateTime(int year, int month, int day, int hour, int minute, int second, int microsecond)
	{
		this->year = year;
		this->month = month;
		this->day = day;
		this->hour = hour;
		this->minute = minute;
		this->second = second;
		this->microsecond = microsecond;
	}

	void ScePspDateTime::read(Memory *mem, int address)
	{
		year = mem->read16(address);
		month = mem->read16(address + 2);
		day = mem->read16(address + 4);
		hour = mem->read16(address + 6);
		minute = mem->read16(address + 8);
		second = mem->read16(address + 10);
		microsecond = mem->read32(address + 12);
	}

	void ScePspDateTime::write(Memory *mem, int address)
	{
		mem->write16(address, static_cast<short>(year & 0xffff));
		mem->write16(address + 2, static_cast<short>(month & 0xffff));
		mem->write16(address + 4, static_cast<short>(day & 0xffff));
		mem->write16(address + 6, static_cast<short>(hour & 0xffff));
		mem->write16(address + 8, static_cast<short>(minute & 0xffff));
		mem->write16(address + 10, static_cast<short>(second & 0xffff));
		mem->write32(address + 12, microsecond);
	}

	int ScePspDateTime::sizeof_Keyword()
	{
		return 16;
	}
}
