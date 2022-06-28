/*
 *    28/06/2022 -  synced with jpcsp f4fc91f 07/07/2010 - some log missing (replaced with printf's
 */
#include "..\..\PCSPCommon.h"
#include "SceUidManager.h"
#include "..\Types\SceUid.h"

typedef std::map<u32, SceUid> uidmap;


static uidmap uidMap;
static u32 nextUid = 0x1000;

/** classes should call getUid to get a new unique SceUID */
u32 SceUidManager::getNewUid(const std::string &purpose) 
{
	uidMap[nextUid] = SceUid(purpose, nextUid);
	nextUid++;
	return nextUid - 1;
}
/** classes should call checkUidPurpose before using a SceUID
 * @return true is the uid is ok. */
bool SceUidManager::checkUidPurpose(u32 uid, const std::string &purpose, bool allowUnknown) {
	uidmap::const_iterator found = uidMap.find(uid);
	if (found == uidMap.end()) {
		if (!allowUnknown) {
                printf("Attempt to use unknown SceUID (purpose = %s)", purpose.c_str());//Emulator::log.warn("Attempt to use unknown SceUID (purpose = %s)", purpose);
			return false;
		}
		return true;
	}
	else if (found->second.getPurpose() != purpose) {
            printf("Attempt to use SceUID for different purpose (purpose = %s) original = %s", purpose.c_str(),
                   found->second.getPurpose().c_str());  
            // Emulator::log.error("Attempt to use SceUID for different purpose
                                                 // (purpose = %s) original = %s", purpose,found->second.getPurpose());
		return false;
	}
	return true;
}
/** classes should call releaseUid when they are finished with a SceUID
 * @return true on success. */
bool SceUidManager::releaseUid(u32 uid, const std::string &purpose) {
	uidmap::const_iterator found = uidMap.find(uid);
	if (found == uidMap.end()) {
            printf("Attempt to release unknown SceUID (purpose = %s)", purpose.c_str());//Emulator::log.warn("Attempt to release unknown SceUID (purpose = %s)", purpose);
		return false;
	}
	else {
		if (found->second.getPurpose() == purpose) {
			uidMap.erase(found);
			return true;
		}
		else {
                    printf("Attempt to release SceUID for different purpose (purpose = %s) original = %s",
                           purpose.c_str(),
                           found->second.getPurpose().c_str());  // Emulator::log.warn(	"Attempt to release SceUID for different
                                                         // purpose(purpose = %s) original =
                                                         // %s",purpose,found->second.getPurpose());
			return false;
		}
	}
}

