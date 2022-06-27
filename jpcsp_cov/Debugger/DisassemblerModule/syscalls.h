#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <string>
#include <vector>
#include <stdexcept>
#include <utility>

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
namespace jpcsp::Debugger::DisassemblerModule
{

	/**
	 *
	 * @author George
	 */
	class syscalls
	{
	 public:
		 enum class calls
		 {
			 sceKernelRegisterSubIntrHandler = 0x2000,
			 sceKernelReleaseSubIntrHandler = 0x2001,
			 sceKernelEnableSubIntr = 0x2002,
			 sceKernelDisableSubIntr = 0x2003,
			 sceKernelSuspendSubIntr = 0x2004,
			 sceKernelResumeSubIntr = 0x2005,
			 sceKernelIsSubInterruptOccurred = 0x2006,
			 QueryIntrHandlerInfo = 0x2007,
			 sceKernelRegisterUserSpaceIntrStack = 0x2008,
			 _sceKernelReturnFromCallback = 0x2009,
			 sceKernelRegisterThreadEventHandler = 0x200a,
			 sceKernelReleaseThreadEventHandler = 0x200b,
			 sceKernelReferThreadEventHandlerStatus = 0x200c,
			 sceKernelCreateCallback = 0x200d,
			 sceKernelDeleteCallback = 0x200e,
			 sceKernelNotifyCallback = 0x200f,
			 sceKernelCancelCallback = 0x2010,
			 sceKernelGetCallbackCount = 0x2011,
			 sceKernelCheckCallback = 0x2012,
			 sceKernelReferCallbackStatus = 0x2013,
			 sceKernelSleepThread = 0x2014,
			 sceKernelSleepThreadCB = 0x2015,
			 sceKernelWakeupThread = 0x2016,
			 sceKernelCancelWakeupThread = 0x2017,
			 sceKernelSuspendThread = 0x2018,
			 sceKernelResumeThread = 0x2019,
			 sceKernelWaitThreadEnd = 0x201a,
			 sceKernelWaitThreadEndCB = 0x201b,
			 sceKernelDelayThread = 0x201c,
			 sceKernelDelayThreadCB = 0x201d,
			 sceKernelDelaySysClockThread = 0x201e,
			 sceKernelDelaySysClockThreadCB = 0x201f,
			 sceKernelCreateSema = 0x2020,
			 sceKernelDeleteSema = 0x2021,
			 sceKernelSignalSema = 0x2022,
			 sceKernelWaitSema = 0x2023,
			 sceKernelWaitSemaCB = 0x2024,
			 sceKernelPollSema = 0x2025,
			 sceKernelCancelSema = 0x2026,
			 sceKernelReferSemaStatus = 0x2027,
			 sceKernelCreateEventFlag = 0x2028,
			 sceKernelDeleteEventFlag = 0x2029,
			 sceKernelSetEventFlag = 0x202a,
			 sceKernelClearEventFlag = 0x202b,
			 sceKernelWaitEventFlag = 0x202c,
			 sceKernelWaitEventFlagCB = 0x202d,
			 sceKernelPollEventFlag = 0x202e,
			 sceKernelCancelEventFlag = 0x202f,
			 sceKernelReferEventFlagStatus = 0x2030,
			 sceKernelCreateMbx = 0x2031,
			 sceKernelDeleteMbx = 0x2032,
			 sceKernelSendMbx = 0x2033,
			 sceKernelReceiveMbx = 0x2034,
			 sceKernelReceiveMbxCB = 0x2035,
			 sceKernelPollMbx = 0x2036,
			 sceKernelCancelReceiveMbx = 0x2037,
			 sceKernelReferMbxStatus = 0x2038,
			 sceKernelCreateMsgPipe = 0x2039,
			 sceKernelDeleteMsgPipe = 0x203a,
			 sceKernelSendMsgPipe = 0x203b,
			 sceKernelSendMsgPipeCB = 0x203c,
			 sceKernelTrySendMsgPipe = 0x203d,
			 sceKernelReceiveMsgPipe = 0x203e,
			 sceKernelReceiveMsgPipeCB = 0x203f,
			 sceKernelTryReceiveMsgPipe = 0x2040,
			 sceKernelCancelMsgPipe = 0x2041,
			 sceKernelReferMsgPipeStatus = 0x2042,
			 sceKernelCreateVpl = 0x2043,
			 sceKernelDeleteVpl = 0x2044,
			 sceKernelAllocateVpl = 0x2045,
			 sceKernelAllocateVplCB = 0x2046,
			 sceKernelTryAllocateVpl = 0x2047,
			 sceKernelFreeVpl = 0x2048,
			 sceKernelCancelVpl = 0x2049,
			 sceKernelReferVplStatus = 0x204a,
			 sceKernelCreateFpl = 0x204b,
			 sceKernelDeleteFpl = 0x204c,
			 sceKernelAllocateFpl = 0x204d,
			 sceKernelAllocateFplCB = 0x204e,
			 sceKernelTryAllocateFpl = 0x204f,
			 sceKernelFreeFpl = 0x2050,
			 sceKernelCancelFpl = 0x2051,
			 sceKernelReferFplStatus = 0x2052,
			 ThreadManForUser_0E927AED = 0x2053,
			 sceKernelUSec2SysClock = 0x2054,
			 sceKernelUSec2SysClockWide = 0x2055,
			 sceKernelSysClock2USec = 0x2056,
			 sceKernelSysClock2USecWide = 0x2057,
			 sceKernelGetSystemTime = 0x2058,
			 sceKernelGetSystemTimeWide = 0x2059,
			 sceKernelGetSystemTimeLow = 0x205a,
			 sceKernelSetAlarm = 0x205b,
			 sceKernelSetSysClockAlarm = 0x205c,
			 sceKernelCancelAlarm = 0x205d,
			 sceKernelReferAlarmStatus = 0x205e,
			 sceKernelCreateVTimer = 0x205f,

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
