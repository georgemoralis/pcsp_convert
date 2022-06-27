#pragma once

#include "../GeneralJpcspException.h"
#include <unordered_map>
#include <any>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace jpcsp::HLE { class SceUID; }

/*
This file is part of jpcsp.

Jpcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Jpcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Jpcsp.  If not, see <http://www.gnu.org/licenses/>.
 */
/* SceUID Manager
 * Function:
 * Allocates SceUIDs to other modules.
 *
 * Why:
 * So we can avoid duplicate SceUID and detect when SceUID for one
 * purpose is used for another, example: thread UID used in semaphore.
 */
namespace jpcsp::HLE
{

	using HashMap = java::util::HashMap;
	using GeneralJpcspException = jpcsp::GeneralJpcspException;

	class SceUIDMan
	{
	private:
		static SceUIDMan *instance;
		static std::unordered_map<int, SceUID*> uids;
		static int uidnext;

	public:
		static SceUIDMan *get_instance();

	private:
		SceUIDMan();

		/** classes should call getUid to get a new unique SceUID */
	public:
		virtual int getNewUid(std::any purpose);

		/** classes should call checkUidPurpose before using a SceUID */
		virtual void checkUidPurpose(int uid, std::any purpose);

		/** classes should call checkUidPurpose before using a SceUID */
		virtual void checkUidPurpose(int uid, std::any purpose, bool allowUnknown);

		/** classes should call releaseUid when they are finished with a SceUID */
		virtual void releaseUid(int uid, std::any purpose);

	private:
		class SceUID
		{
		private:
			SceUIDMan *outerInstance;

			std::any purpose;
			int uid = 0;

		public:
			virtual ~SceUID()
			{
				delete outerInstance;
			}

			SceUID(SceUIDMan *outerInstance, std::any purpose);

			virtual std::any getPurpose();

			virtual int getUid();
		};
	};

}
