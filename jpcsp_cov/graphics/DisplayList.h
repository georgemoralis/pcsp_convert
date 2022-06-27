#pragma once

#include "../Emulator.h"
#include <string>
#include <unordered_map>
#include <mutex>
#include "exceptionhelper.h"

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
namespace jpcsp::graphics
{

	using Iterator = java::util::Iterator;
	using HashMap = java::util::HashMap;
	using Semaphore = java::util::concurrent::Semaphore;


	// Use the locks for reading/writing member variables and calling member methods
	class DisplayList
	{
		private:
			std::mutex lock_object;


	public:
		static constexpr int DONE = 0;
		static constexpr int QUEUED = 1;
		static constexpr int DRAWING_DONE = 2;
		static constexpr int STALL_REACHED = 3;
		static constexpr int CANCEL_DONE = 4;
		//sceGuSendList [int mode
		static constexpr int GU_TAIL = 0;
		static constexpr int GU_HEAD = 1;

	protected:
		static Semaphore *displayListLock;

	private:
		static std::unordered_map<int, DisplayList*> displayLists;
		static int ids;

	public:
		int __super = 0;
		int pc = 0;
		int *stack = new int[32];
		int stackIndex = 0;
		int status = 0;
		int id = 0;

		int start = 0;
		int stallAddress = 0;
		const int callbackId;
		const int arg;

		virtual ~DisplayList()
		{
			delete[] stack;
		}

		DisplayList(int startList, int stall, int callbackId, int arg);

		static void Initialise();

		static void addDisplayList(DisplayList *list);

		static bool removeDisplayList(int id);

		static DisplayList *getDisplayList(int id);

		static Iterator<DisplayList*> *iterator();

		static void Lock();

		static void Unlock();

		virtual std::string toString();
	};

}
