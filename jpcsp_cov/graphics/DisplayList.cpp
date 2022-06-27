using namespace std;

#include "DisplayList.h"

namespace jpcsp::graphics
{
	using Iterator = java::util::Iterator;
	using HashMap = java::util::HashMap;
	using Semaphore = java::util::concurrent::Semaphore;
	using Emulator = jpcsp::Emulator;
java::util::concurrent::Semaphore *DisplayList::displayListLock = new java::util::concurrent::Semaphore(1, true);
unordered_map<int, DisplayList*> DisplayList::displayLists;
int DisplayList::ids = 0;

	DisplayList::DisplayList(int startList, int stall, int callbackId, int arg) : callbackId(callbackId), arg(arg)
	{
		this->start = startList;
		this->stallAddress = stall;

		__super = 0x08000000;
		pc = startList;
		stackIndex = 0;
		if (pc == stallAddress)
		{
			status = DisplayList::STALL_REACHED;
		}
		else
		{
			status = DisplayList::QUEUED;
		}
		//list.id = ids++;
	}

	void DisplayList::Initialise()
	{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		scoped_lock<mutex> lock(DisplayList::class);
		displayLists = unordered_map<int, DisplayList*>();
		ids = 0;
	}

	void DisplayList::addDisplayList(DisplayList *list)
	{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		scoped_lock<mutex> lock(DisplayList::class);
		// create the id outside of the constructor, inside a synchronized block so it is thread safe
		list->id = ids++;
		displayLists.emplace(list->id, list);
	}

	bool DisplayList::removeDisplayList(int id)
	{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		scoped_lock<mutex> lock(DisplayList::class);
		return (displayLists.erase(id) != nullptr);
	}

	DisplayList *DisplayList::getDisplayList(int id)
	{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		scoped_lock<mutex> lock(DisplayList::class);
		return displayLists[id];
	}

	Iterator<DisplayList*> *DisplayList::iterator()
	{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		scoped_lock<mutex> lock(DisplayList::class);
		return displayLists.values().begin();
	}

	void DisplayList::Lock()
	{
		try
		{
			displayListLock->acquire();
		}
		catch (const InterruptedException &e)
		{
		}
	}

	void DisplayList::Unlock()
	{
		displayListLock->release();
	}

	string DisplayList::toString()
	{
		scoped_lock<mutex> lock(lock_object);
		return "id = " + to_string(id) + ", start address = " + Integer::toHexString(start) + ", end address = " + Integer::toHexString(stallAddress) + ", initial command instruction = " + Integer::toHexString(Emulator::getMemory()->read32(pc));
	}
}
