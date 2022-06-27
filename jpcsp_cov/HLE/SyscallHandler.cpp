using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "SyscallHandler.h"
#include "ThreadMan.h"
#include "pspiofilemgr.h"
#include "pspstdio.h"
#include "psputils.h"
#include "pspSysMem.h"
#include "LoadExec.h"
#include "pspge.h"
#include "psprtc.h"
#include "pspAudio.h"
#include "pspdisplay.h"
#include "pspctrl.h"
#include "../Debugger/DisassemblerModule/syscalls.h"

namespace jpcsp::HLE
{
	using namespace jpcsp::Debugger::DisassemblerModule;
	using Emulator = jpcsp::Emulator;
	using GeneralJpcspException = jpcsp::GeneralJpcspException;

	void SyscallHandler::syscall(int code)
	{
		int *gpr = Emulator::getProcessor()->gpr;

		// Some syscalls implementation throw GeneralJpcspException,
		// and Processor isn't setup to catch exceptions so we'll do it
		// here for now, or we could just stop throwing exceptions.
		// Also we need to decide whether to pass arguments to the functions,
		// or let them read the registers they want themselves.
		try
		{
			// Currently using FW1.50 codes
			switch (code)
			{
			  //  case 0x2000: //sceKernelRegisterSubIntrHandler
			  //  case 0x2001: // sceKernelReleaseSubIntrHandler
		//  case 0x2002: //sceKernelEnableSubIntr
		//  case 0x2003: //sceKernelDisableSubIntr
		//  case 0x2004: //sceKernelSuspendSubIntr
		//  case 0x2005: //sceKernelResumeSubIntr
		//  case 0x2006: //sceKernelIsSubInterruptOccurred
		//  case 0x2007: //QueryIntrHandlerInfo
		//  case 0x2008: //sceKernelRegisterUserSpaceIntrStack
		//  case 0x2009: //_sceKernelReturnFromCallback
		//  case 0x200a: //sceKernelRegisterThreadEventHandler
		//  case 0x200b: //sceKernelReleaseThreadEventHandler
		//  case 0x200c: //sceKernelReferThreadEventHandlerStatus
				case 0x200d:
					ThreadMan::get_instance()->ThreadMan_sceKernelCreateCallback(gpr[4], gpr[5], gpr[6]);
					break;
			   // case 0x200e: //sceKernelDeleteCallback
			   // case 0x200f: //sceKernelNotifyCallback
			  //  case 0x2010: //sceKernelCancelCallback
			  //  case 0x2011: //sceKernelGetCallbackCount
			  //  case 0x2012: //sceKernelCheckCallback
			  //  case 0x2013: //sceKernelReferCallbackStatus
				case 0x2014:
					ThreadMan::get_instance()->ThreadMan_sceKernelSleepThread();
					break;
				case 0x2015:
					ThreadMan::get_instance()->ThreadMan_sceKernelSleepThreadCB();
					break;
				//case 0x2016: //sceKernelWakeupThread
		//case 0x2017: ///sceKernelCancelWakeupThread
		//case 0x2018: //sceKernelSuspendThread
		//case 0x2019: //sceKernelResumeThread
		//case 0x201a: //sceKernelWaitThreadEnd
		//case 0x201b: //sceKernelWaitThreadEndCB
				case 0x201c:
					ThreadMan::get_instance()->ThreadMan_sceKernelDelayThread(gpr[4]);
					break;
				 //sceKernelDelayThreadCB(0x201d),
		 //sceKernelDelaySysClockThread(0x201e),
		// sceKernelDelaySysClockThreadCB(0x201f),
		// sceKernelCreateSema(0x2020),
		// sceKernelDeleteSema(0x2021),
		 //sceKernelSignalSema(0x2022),
		 //sceKernelWaitSema(0x2023),
		 //sceKernelWaitSemaCB(0x2024),
		// sceKernelPollSema(0x2025),
		 //sceKernelCancelSema(0x2026),
		 //sceKernelReferSemaStatus(0x2027),
		 //sceKernelCreateEventFlag(0x2028),
		// sceKernelDeleteEventFlag(0x2029),
		// sceKernelSetEventFlag(0x202a),
		// sceKernelClearEventFlag(0x202b),
		// sceKernelWaitEventFlag(0x202c),
		// sceKernelWaitEventFlagCB(0x202d),
		// sceKernelPollEventFlag(0x202e),
		// sceKernelCancelEventFlag(0x202f),
		// sceKernelReferEventFlagStatus(0x2030),
		// sceKernelCreateMbx(0x2031),
		// sceKernelDeleteMbx(0x2032),
		// sceKernelSendMbx(0x2033),
		// sceKernelReceiveMbx(0x2034),
		// sceKernelReceiveMbxCB(0x2035),
		// sceKernelPollMbx(0x2036),
		// sceKernelCancelReceiveMbx(0x2037),
		// sceKernelReferMbxStatus(0x2038),
		// sceKernelCreateMsgPipe(0x2039),
		// sceKernelDeleteMsgPipe(0x203a),
		// sceKernelSendMsgPipe(0x203b),
		// sceKernelSendMsgPipeCB(0x203c),
		// sceKernelTrySendMsgPipe(0x203d),
		// sceKernelReceiveMsgPipe(0x203e),
		// sceKernelReceiveMsgPipeCB(0x203f),
		// sceKernelTryReceiveMsgPipe(0x2040),
		// sceKernelCancelMsgPipe(0x2041),
		// sceKernelReferMsgPipeStatus(0x2042),
		// sceKernelCreateVpl(0x2043),
		// sceKernelDeleteVpl(0x2044),
		// sceKernelAllocateVpl(0x2045),
		// sceKernelAllocateVplCB(0x2046),
		// sceKernelTryAllocateVpl(0x2047),
		// sceKernelFreeVpl(0x2048),
		// sceKernelCancelVpl(0x2049),
		// sceKernelReferVplStatus(0x204a),
		// sceKernelCreateFpl(0x204b),
		// sceKernelDeleteFpl(0x204c),
		// sceKernelAllocateFpl(0x204d),
		// sceKernelAllocateFplCB(0x204e),
		// sceKernelTryAllocateFpl(0x204f),
		// sceKernelFreeFpl(0x2050),
		// sceKernelCancelFpl(0x2051),
		// sceKernelReferFplStatus(0x2052),
		// ThreadManForUser_0E927AED(0x2053),
		// sceKernelUSec2SysClock(0x2054),
		// sceKernelUSec2SysClockWide(0x2055),
		// sceKernelSysClock2USec(0x2056),
		// sceKernelSysClock2USecWide(0x2057),
		// sceKernelGetSystemTime(0x2058),
		// sceKernelGetSystemTimeWide(0x2059),
		// sceKernelGetSystemTimeLow(0x205a),
		// sceKernelSetAlarm(0x205b),
		// sceKernelSetSysClockAlarm(0x205c),
		// sceKernelCancelAlarm(0x205d),
		// sceKernelReferAlarmStatus(0x205e),
		// sceKernelCreateVTimer(0x205f),
		// sceKernelDeleteVTimer(0x2060),
		// sceKernelGetVTimerBase(0x2061),
		// sceKernelGetVTimerBaseWide(0x2062),
		// sceKernelGetVTimerTime(0x2063),
		// sceKernelGetVTimerTimeWide(0x2064),
		// sceKernelSetVTimerTime(0x2065),
		// sceKernelSetVTimerTimeWide(0x2066),
		// sceKernelStartVTimer(0x2067),
		// sceKernelStopVTimer(0x2068),
		// sceKernelSetVTimerHandler(0x2069),
		// sceKernelSetVTimerHandlerWide(0x206a),
		// sceKernelCancelVTimerHandler(0x206b),
		// sceKernelReferVTimerStatus(0x206c),
				case 0x206d:
					ThreadMan::get_instance()->ThreadMan_sceKernelCreateThread(gpr[4], gpr[5], gpr[6], gpr[7], gpr[8], gpr[9]);
					break;
				case 0x206e:
					ThreadMan::get_instance()->ThreadMan_sceKernelDeleteThread(gpr[4]);
					break;
				case 0x206f:
					ThreadMan::get_instance()->ThreadMan_sceKernelStartThread(gpr[4], gpr[5], gpr[6]);
					break;
				case 0x2070:
				case 0x2071:
					ThreadMan::get_instance()->ThreadMan_sceKernelExitThread(gpr[4]);
					break;
				case 0x2072:
					ThreadMan::get_instance()->ThreadMan_sceKernelExitDeleteThread(gpr[4]);
					break;
				case 0x2073:
					ThreadMan::get_instance()->ThreadMan_sceKernelTerminateThread(gpr[4]);
					break;
				 //sceKernelTerminateDeleteThread(0x2074),
		// sceKernelSuspendDispatchThread(0x2075),
		 //sceKernelResumeDispatchThread(0x2076),
		// sceKernelChangeCurrentThreadAttr(0x2077),
		// sceKernelChangeThreadPriority(0x2078),
		// sceKernelRotateThreadReadyQueue(0x2079),
		// sceKernelReleaseWaitThread(0x207a),
				case 0x207b:
					ThreadMan::get_instance()->ThreadMan_sceKernelGetThreadId();
					break;
				// sceKernelGetThreadCurrentPriority(0x207c),
		// sceKernelGetThreadExitStatus(0x207d),
		// sceKernelCheckThreadStack(0x207e),
		// sceKernelGetThreadStackFreeSize(0x207f),
				case 0x2080:
					ThreadMan::get_instance()->ThreadMan_sceKernelReferThreadStatus(gpr[4], gpr[5]);
					break;
				// sceKernelReferThreadRunStatus(0x2081),
		// sceKernelReferSystemStatus(0x2082),
		// sceKernelGetThreadmanIdList(0x2083),
		// sceKernelGetThreadmanIdType(0x2084),
		// sceKernelReferThreadProfiler(0x2085),
		// sceKernelReferGlobalProfiler(0x2086),
		// sceIoPollAsync(0x2087),
		// sceIoWaitAsync(0x2088),
		// sceIoWaitAsyncCB(0x2089),
		// sceIoGetAsyncStat(0x208a),
		// sceIoChangeAsyncPriority(0x208b),
		// sceIoSetAsyncCallback(0x208c),
				case 0x208d: // sceIoClose
					pspiofilemgr::get_instance()->sceIoClose(gpr[4]);
					break;
		// sceIoCloseAsync(0x208e),
				case 0x208f: // sceIoOpen
					pspiofilemgr::get_instance()->sceIoOpen(gpr[4], gpr[5], gpr[6]);
					break;
		// sceIoOpenAsync(0x2090),
				case 0x2091: //sceIoRead
					pspiofilemgr::get_instance()->sceIoRead(gpr[4], gpr[5], gpr[6]);
					break;
		// sceIoReadAsync(0x2092),
				case 0x2093: // sceIoWrite
					pspiofilemgr::get_instance()->sceIoWrite(gpr[4], gpr[5], gpr[6]);
					break;
		// sceIoWriteAsync(0x2094),
		// sceIoLseek(0x2095),
		// sceIoLseekAsync(0x2096),
				case 0x2097:
					pspiofilemgr::get_instance()->sceIoLseek32(gpr[4], gpr[5], gpr[6]);
					break;
		// sceIoLseek32Async(0x2098),
		// sceIoIoctl(0x2099),
		// sceIoIoctlAsync(0x209a),
			case 0x209b: //sceIoDopen
					pspiofilemgr::get_instance()->sceIoDopen(gpr[4]);
					break;
			case 0x209c:
					pspiofilemgr::get_instance()->sceIoDread(gpr[4], gpr[5]);
					break;
			case 0x209d:
					pspiofilemgr::get_instance()->sceIoDclose(gpr[4]);
					break;
		// sceIoRemove(0x209e),
			case 0x209f:
					pspiofilemgr::get_instance()->sceIoMkdir(gpr[4], gpr[5]);
					break;
		// sceIoRmdir(0x20a0),
				case 0x20a1: //sceChDir
					pspiofilemgr::get_instance()->sceIoChdir(gpr[4]);
					break;
		// sceIoSync(0x20a2),
				case 0x20a3:
					pspiofilemgr::get_instance()->sceIoGetstat(gpr[4], gpr[5]);
					break;
		// sceIoChstat(0x20a4),
		// sceIoRename(0x20a5),
		// sceIoDevctl(0x20a6),
		// sceIoGetDevType(0x20a7),
		// sceIoAssign(0x20a8),
		// sceIoUnassign(0x20a9),
		// sceIoCancel(0x20aa),
		// IoFileMgrForUser_5C2BE2CC(0x20ab),
		// sceKernelStdioRead(0x20ac),
		// sceKernelStdioLseek(0x20ad),
		// sceKernelStdioSendChar(0x20ae),
		// sceKernelStdioWrite(0x20af),
		// sceKernelStdioClose(0x20b0),
		 //sceKernelStdioOpen(0x20b1),
				case 0x20b2:
					pspstdio::get_instance()->sceKernelStdin();
					break;
				case 0x20b3:
					pspstdio::get_instance()->sceKernelStdout();
					break;
				case 0x20b4:
					pspstdio::get_instance()->sceKernelStderr();
					break;
				case 0x20b5:
					psputils::get_instance()->sceKernelDcacheInvalidateRange(gpr[4], gpr[5]);
					break;
		// sceKernelIcacheInvalidateRange(0x20b6),
		// sceKernelUtilsMd5Digest(0x20b7),
		// sceKernelUtilsMd5BlockInit(0x20b8),
		// sceKernelUtilsMd5BlockUpdate(0x20b9),
		// sceKernelUtilsMd5BlockResult(0x20ba),
		// sceKernelUtilsSha1Digest(0x20bb),
		// sceKernelUtilsSha1BlockInit(0x20bc),
		// sceKernelUtilsSha1BlockUpdate(0x20bd),
		// sceKernelUtilsSha1BlockResult(0x20be),
				case 0x20bf:
					psputils::get_instance()->sceKernelUtilsMt19937Init(gpr[4], gpr[5]);
					break;
				case 0x20c0:
					psputils::get_instance()->sceKernelUtilsMt19937UInt(gpr[4]);
					break;
		// sceKernelGetGPI(0x20c1),
		// sceKernelSetGPO(0x20c2),
				case 0x20c3:
					psputils::get_instance()->sceKernelLibcClock();
					break;
				case 0x20c4:

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
