#pragma once


#define PSP_THREAD_ATTR_USER 0x80000000
#define PSP_THREAD_ATTR_USBWLAN 0xa0000000
#define PSP_THREAD_ATTR_VSH 0xc0000000
#define PSP_THREAD_ATTR_KERNEL 0x00001000 //TODO are module/thread attr interchangeable? (probably yes)
#define PSP_THREAD_ATTR_VFPU 0x00004000
#define PSP_THREAD_ATTR_SCRATCH_SRAM 0x00008000
#define PSP_THREAD_ATTR_NO_FILLSTACK 0x00100000  // Disables filling the stack with 0xFF on creation.
#define PSP_THREAD_ATTR_CLEAR_STACK 0x00200000   // Clear the stack when the thread is deleted.

// PspThreadStatus
#define PSP_THREAD_RUNNING 0x00000001
#define PSP_THREAD_READY 0x00000002
#define PSP_THREAD_WAITING 0x00000004
#define PSP_THREAD_SUSPEND 0x00000008
#define PSP_THREAD_STOPPED 0x00000010
#define PSP_THREAD_KILLED 0x00000020

#pragma pack(push, 1)
struct SceKernelThreadInfo_t {
    int size;
    char name[32];
    int attr;
    int status;
    int entry_addr;
    int stack_addr;
    int stackSize;
    int gpReg_addr;
    int initPriority;
    int currentPriority;
    int waitType;  // 3 = sema
    int waitId;
    int wakeupCount;
    int exitStatus;
    u64 runClocks;
    int intrPreemptCount;
    int threadPreemptCount;
    int releaseCount;
};

#pragma pack(pop)
class SceKernelThreadInfo : public SceKernelThreadInfo_t {
   public:

};
namespace ThreadMan {};
