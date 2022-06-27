#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "../Emulator.h"
#include "../GeneralJpcspException.h"
#include "../Memory.h"
#include "../MemoryMap.h"
#include "../Processor.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace jpcsp::HLE { class SceKernelThreadInfo; }

/*
Thread Manager
Function:
- HLE everything in http://psp.jim.sh/pspsdk-doc/group__ThreadMan.html
- Schedule threads

Note:
- incomplete and not fully tested


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
namespace jpcsp::HLE
{

	using Comparator = java::util::Comparator;
	using HashMap = java::util::HashMap;
	using GeneralJpcspException = jpcsp::GeneralJpcspException;
	using namespace jpcsp::util;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;


	class ThreadMan
	{
	private:
		static ThreadMan *instance;
		static std::unordered_map<int, SceKernelThreadInfo*> threadlist;
		SceKernelThreadInfo *current_thread;
		SceKernelThreadInfo *idle0, *idle1;
		int continuousIdleCycles = 0; // watch dog timer

		// stack allocation MOVED TO PSPSYSMEM
		//private static int stackAllocated;

	public:
		virtual ~ThreadMan()
		{
			delete current_thread;
			delete idle0;
			delete idle1;
		}

		static ThreadMan *get_instance();

	private:
		ThreadMan();

		/** call this when resetting the emulator
		 * @param entry_addr entry from ELF header
		 * @param attr from sceModuleInfo ELF section header */
	public:
		virtual void Initialise(int entry_addr, int attr);

	private:
		void install_idle_threads();

		/** to be called from the main emulation loop */
	public:
		virtual void step();

	private:
		void contextSwitch(SceKernelThreadInfo *newthread);

		// This function must have the property of never returning current_thread, unless current_thread is already null
		SceKernelThreadInfo *nextThread();


	public:
		virtual void ThreadMan_sceKernelCreateThread(int name_addr, int entry_addr, int initPriority, int stackSize, int attr, int option_addr);

		/** terminate thread a0 */
		virtual void ThreadMan_sceKernelTerminateThread(int a0);

		/** delete thread a0 */
		virtual void ThreadMan_sceKernelDeleteThread(int a0);

		virtual void ThreadMan_sceKernelStartThread(int a0, int a1, int a2);

		/** exit the current thread */
		virtual void ThreadMan_sceKernelExitThread(int exitStatus);

		/** exit the current thread, then delete it */
		virtual void ThreadMan_sceKernelExitDeleteThread(int exitStatus);

		/** sleep the current thread until a registered callback is triggered */
		virtual void ThreadMan_sceKernelSleepThreadCB();

		/** sleep the current thread */
		virtual void ThreadMan_sceKernelSleepThread();

		/** sleep the current thread for a certain number of microseconds */
		virtual void ThreadMan_sceKernelDelayThread(int a0);

		virtual void ThreadMan_sceKernelCreateCallback(int a0, int a1, int a2);

		virtual void ThreadMan_sceKernelGetThreadId();

		virtual void ThreadMan_sceKernelReferThreadStatus(int a0, int a1);

	private:
		class SceKernelCallbackInfo
		{
		private:
			ThreadMan *outerInstance;

			std::string name;
			int threadId = 0;
			int callback_addr = 0;
			int callback_arg_addr = 0;
			int notifyCount = 0;
			int notifyArg = 0;

			// internal variables
			int uid = 0;

		public:
			virtual ~SceKernelCallbackInfo()
			{
				delete outerInstance;
			}

			SceKernelCallbackInfo(ThreadMan *outerInstance, const std::string &name, int threadId, int callback_addr, int callback_arg_addr);
		};

	public:
		enum class PspThreadStatus
		{
			PSP_THREAD_RUNNING = 1,
			PSP_THREAD_READY = 2,
			PSP_THREAD_WAITING = 4,
			PSP_THREAD_SUSPEND = 8,
			PSP_THREAD_STOPPED = 16,
			PSP_THREAD_KILLED = 32
//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//			private int value;
//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//			private PspThreadStatus(int value)
	//		{
	//			this.value = value;
	//		}
//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//			public int getValue()
	//		{
	//			return value;
	//		}
		};

		class PspThreadStatusHelper
		{
		private:
			static std::vector<std::pair<PspThreadStatus, std::string>> pairs()
			{
				return
				{
					{PspThreadStatus::PSP_THREAD_RUNNING, "PSP_THREAD_RUNNING"},
					{PspThreadStatus::PSP_THREAD_READY, "PSP_THREAD_READY"},
					{PspThreadStatus::PSP_THREAD_WAITING, "PSP_THREAD_WAITING"},
					{PspThreadStatus::PSP_THREAD_SUSPEND, "PSP_THREAD_SUSPEND"},
					{PspThreadStatus::PSP_THREAD_STOPPED, "PSP_THREAD_STOPPED"},
					{PspThreadStatus::PSP_THREAD_KILLED, "PSP_THREAD_KILLED"}
				};
			}

		public:
			static std::vector<PspThreadStatus> values()
			{
				std::vector<PspThreadStatus> temp;
				for (auto pair : pairs())
				{
					temp.push_back(pair.first);
				}
				return temp;
			}

			static std::string enumName(PspThreadStatus value)
			{
				for (auto pair : pairs())
				{
					if (pair.first == value)
						return pair.second;
				}

				throw std::runtime_error("Enum not found.");
			}

			static int ordinal(PspThreadStatus value)
			{
				std::vector<std::pair<PspThreadStatus, std::string>> temp = pairs();
				for (std::size_t i = 0; i < temp.size(); i++)
				{
					if (temp[i].first == value)
						return i;
				}

				throw std::runtime_error("Enum not found.");
			}

			static PspThreadStatus enumFromString(std::string value)
			{
				for (auto pair : pairs())
				{
					if (pair.second == value)

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
