using namespace std;

#include "SceUIDMan.h"

namespace jpcsp::HLE
{
	using HashMap = java::util::HashMap;
	using GeneralJpcspException = jpcsp::GeneralJpcspException;
SceUIDMan *SceUIDMan::instance;
unordered_map<int, SceUID*> SceUIDMan::uids;
int SceUIDMan::uidnext = 0;

	SceUIDMan *SceUIDMan::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new SceUIDMan();
		}
		return instance;
	}

	SceUIDMan::SceUIDMan()
	{
		uids = unordered_map<int, SceUID*>();
		uidnext = 0x1000;
	}

	int SceUIDMan::getNewUid(any purpose)
	{
		SceUID *uid = new SceUID(this, purpose);
		uids.emplace(uid->getUid(), uid);

//JAVA TO C++ CONVERTER TODO TASK: A 'delete uid' statement was not added since uid was passed to a method or constructor. Handle memory management manually.
		return uid->getUid();
	}

	void SceUIDMan::checkUidPurpose(int uid, any purpose)
	{
		checkUidPurpose(uid, purpose, false);
	}

	void SceUIDMan::checkUidPurpose(int uid, any purpose, bool allowUnknown)
	{
		SceUID *found = uids[uid];

		if (found == nullptr)
		{
			if (!allowUnknown)
			{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
				throw GeneralJpcspException("Attempt to use unknown SceUID (purpose='" + purpose.toString() + "')");
			}
		}
		else if (!purpose.equals(found->getPurpose()))
		{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
			throw GeneralJpcspException("Attempt to use SceUID for different purpose (purpose='" + purpose.toString() + "',original='" + found->getPurpose().toString() + "')");
		}
	}

	void SceUIDMan::releaseUid(int uid, any purpose)
	{
		SceUID *found = uids[uid];

		if (found == nullptr)
		{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
			throw GeneralJpcspException("Attempt to release unknown SceUID (purpose='" + purpose.toString() + "')");
		}

		if (purpose.equals(found->getPurpose()))
		{
			uids.erase(found);
		}
		else
		{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
			throw GeneralJpcspException("Attempt to release SceUID for different purpose (purpose='" + purpose.toString() + "',original='" + found->getPurpose().toString() + "')");
		}
	}

	SceUIDMan::SceUID::SceUID(SceUIDMan *outerInstance, any purpose) : outerInstance(outerInstance)
	{
		this->purpose = purpose;
		uid = uidnext++;
	}

	any SceUIDMan::SceUID::getPurpose()
	{
		return purpose;
	}

	int SceUIDMan::SceUID::getUid()
	{
		return uid;
	}
}
