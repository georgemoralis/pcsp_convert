/*
*    28/06/2022 -  synced with jpcsp babaee2 21/5/2022 -completed
*/
#include "..\..\PCSPCommon.h"
#include "SceUid.h"

SceUid::SceUid() {
}

SceUid::SceUid(const std::string &purpose, u32 uid)
	: purpose(purpose), uid(uid)
{
}

SceUid::~SceUid() {
}

std::string SceUid::getPurpose() const {
	return purpose;
}

u32 SceUid::getUid() const {
	return uid;
}
