/*
 *    28/06/2022 -  synced with jpcsp babaee2 21/5/2022 -completed
 */
#pragma once

class SceUid {
public:
	SceUid();
	SceUid(const std::string &purpose, u32 uid);
	~SceUid();

	std::string getPurpose() const;
	u32 getUid() const;

	bool operator < (const SceUid &other) const {
		return uid < other.uid;
	}
private:
	std::string purpose;
	u32 uid;
};
