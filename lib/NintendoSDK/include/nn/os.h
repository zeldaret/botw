/**
 * @file os.h
 * @brief Operating System implementations.
 */

#pragma once

#include <type_traits>

#include <nn/time.h>
#include <nn/types.h>

namespace nn {
namespace os {
namespace detail {
struct InternalCriticalSection {
    u32 Image;
};

struct InternalConditionVariable {
    u32 Image;
};
}  // namespace detail

typedef u64 Tick;

struct LightEventType {
    std::aligned_storage_t<0xc, 4> storage;
};

// https://github.com/misson20000/nn-types/blob/master/nn_os.h
struct EventType {
    nn::os::EventType* _x0;
    nn::os::EventType* _x8;
    bool isSignaled;
    bool initiallySignaled;
    bool shouldAutoClear;
    bool isInit;
    u32 signalCounter;
    u32 signalCounter2;
    nn::os::detail::InternalCriticalSection crit;
    nn::os::detail::InternalConditionVariable condvar;
};
typedef EventType Event;

enum EventClearMode { EventClearMode_ManualClear, EventClearMode_AutoClear };

// https://github.com/misson20000/nn-types/blob/master/nn_os.h
struct ThreadType {
    u64 field_8;
    u64 field_10;
    u64 field_18;
    char field_20[32];
    uint32_t thread_status;
    char field_41;
    u16 field_42;
    uint32_t thread_prio_shift;
    uint64_t thread_stack_base_addr;
    uint64_t thread_stack_base_addr_mirror;
    uint64_t thread_stack_size;
    uint64_t thread_param;
    uint64_t thread_func;
    u64 field_70;
    u64 field_78;
    u64 field_80;
    char field_88[0x100];
    char thread_name[0x20];
    const char* thread_name_addr;
    nn::os::detail::InternalCriticalSection crit;
    nn::os::detail::InternalConditionVariable condvar;
    u32 thread_handle;
};
#ifdef SWITCH
static_assert(sizeof(ThreadType) == 0x1C0, "Wrong size");
#endif

struct MessageQueueType {
    u64 _x0;
    u64 _x8;
    u64 _x10;
    u64 _x18;
    void* Buffer;
    u32 MaxCount;
    u32 Count;
    u32 Offset;
    bool Initialized;
    detail::InternalCriticalSection _x38;
    detail::InternalConditionVariable _x3C;
    detail::InternalConditionVariable _x40;
};

struct ConditionVariableType {};

struct SemaphoreType {
    std::aligned_storage_t<0x28, 8> storage;
};

struct SystemEvent;
struct SystemEventType;

// ARG
void SetHostArgc(s32);
s32 GetHostArgc();
void SetHostArgv(char**);
char** GetHostArgv();

// MEMORY
void InitializeVirtualAddressMemory();
Result AllocateAddressRegion(u64*, u64);
Result AllocateMemory(u64*, u64);
Result AllocateMemoryPages(u64, u64);
void AllocateMemoryBlock(u64*, u64);
void FreeMemoryBlock(u64, u64);
void SetMemoryHeapSize(u64);

// MUTEX
struct MutexType {
    u8 _state;
    bool _isRecursive;
    int _lockLevel;
    int _nestCount;
    nn::os::ThreadType* _ownerThread;
    union {
        int32_t _mutexImage[1];
        nn::os::detail::InternalCriticalSection _mutex;
    };
};

void InitializeMutex(nn::os::MutexType*, bool, s32);
void FinalizeMutex(nn::os::MutexType*);
void LockMutex(nn::os::MutexType*);
bool TryLockMutex(nn::os::MutexType*);
void UnlockMutex(nn::os::MutexType*);
bool IsMutexLockedByCurrentThread(nn::os::MutexType const*);

// QUEUE
void InitializeMessageQueue(nn::os::MessageQueueType*, u64* buf, u64 queueCount);
void FinalizeMessageQueue(nn::os::MessageQueueType*);

bool TrySendMessageQueue(MessageQueueType*, u64);
void SendMessageQueue(MessageQueueType*, u64);
bool TimedSendMessageQueue(MessageQueueType*, u64, nn::TimeSpan);

bool TryReceiveMessageQueue(u64* out, MessageQueueType*);
void ReceiveMessageQueue(u64* out, MessageQueueType*);
bool TimedReceiveMessageQueue(u64* out, MessageQueueType*, nn::TimeSpan);

bool TryPeekMessageQueue(u64*, MessageQueueType const*);
void PeekMessageQueue(u64*, MessageQueueType const*);
bool TimedPeekMessageQueue(u64*, MessageQueueType const*);

bool TryJamMessageQueue(nn::os::MessageQueueType*, u64);
void JamMessageQueue(nn::os::MessageQueueType*, u64);
bool TimedJamMessageQueue(nn::os::MessageQueueType*, u64, nn::TimeSpan);

// CONDITION VARIABLE
void InitializeConditionVariable(ConditionVariableType*);
void FinalizeConditionVariable(ConditionVariableType*);

void SignalConditionVariable(ConditionVariableType*);
void BroadcastConditionVariable(ConditionVariableType*);
void WaitConditionVariable(ConditionVariableType*);
u8 TimedWaitConditionVariable(ConditionVariableType*, MutexType*, nn::TimeSpan);

// THREAD
Result CreateThread(nn::os::ThreadType*, void (*)(void*), void* arg, void* srcStack, u64 stackSize,
                    s32 priority, s32 coreNum);
Result CreateThread(nn::os::ThreadType*, void (*)(void*), void* arg, void* srcStack, u64 stackSize,
                    s32 priority);
void DestroyThread(nn::os::ThreadType*);
void StartThread(nn::os::ThreadType*);
void SetThreadName(nn::os::ThreadType*, char const* threadName);
void SetThreadNamePointer(nn::os::ThreadType*, char const*);
char* GetThreadNamePointer(nn::os::ThreadType const*);
nn::os::ThreadType* GetCurrentThread();
void GetCurrentStackInfo(uintptr_t* stack_addr, size_t* stack_size);
s32 ChangeThreadPriority(nn::os::ThreadType* thread, s32 priority);
s32 GetThreadPriority(nn::os::ThreadType const* thread);
u64 GetThreadId(const nn::os::ThreadType* thread);
void YieldThread();
void SuspendThread(nn::os::ThreadType*);
void ResumeThread(nn::os::ThreadType*);
void SleepThread(nn::TimeSpan);
void WaitThread(nn::os::ThreadType*);
void SetThreadCoreMask(nn::os::ThreadType*, int, u64 mask);

// EVENTS
void InitializeEvent(EventType*, bool initiallySignaled, EventClearMode eventClearMode);
void FinalizeEvent(EventType*);
void SignalEvent(EventType*);
void WaitEvent(EventType*);
bool TryWaitEvent(EventType*);
bool TimedWaitEvent(EventType*, nn::TimeSpan);
void ClearEvent(EventType*);

// LIGHT EVENTS
void InitializeLightEvent(LightEventType*, bool initiallySignaled, EventClearMode eventClearMode);
void FinalizeLightEvent(LightEventType*);
void SignalLightEvent(LightEventType*);
void WaitLightEvent(LightEventType*);
bool TimedWaitLightEvent(LightEventType*, nn::TimeSpan);
void ClearLightEvent(LightEventType*);

TimeSpan ConvertToTimeSpan(Tick ticks);

// SEMAPHORES
void InitializeSemaphore(SemaphoreType* semaphore, s32 initial_count, s32 max_count);
void FinalizeSemaphore(SemaphoreType* semaphore);
void AcquireSemaphore(SemaphoreType* semaphore);
bool TryAcquireSemaphore(SemaphoreType* semaphore);
void ReleaseSemaphore(SemaphoreType* semaphore);

// EXCEPTION HANDLING
typedef union {
    u64 x;  ///< 64-bit AArch64 register view.
    u32 w;  ///< 32-bit AArch64 register view.
    u32 r;  ///< AArch32 register view.
} CpuRegister;
/// Armv8 NEON register.

typedef union {
    u128 v;    ///< 128-bit vector view.
    double d;  ///< 64-bit double-precision view.
    float s;   ///< 32-bit single-precision view.
} FpuRegister;

struct UserExceptionInfo {
    u32 ErrorDescription;  ///< See \ref ThreadExceptionDesc.
    u32 pad[3];

    CpuRegister CpuRegisters[29];  ///< GPRs 0..28. Note: also contains AArch32 registers.
    CpuRegister FP;                ///< Frame pointer.
    CpuRegister LR;                ///< Link register.
    CpuRegister SP;                ///< Stack pointer.
    CpuRegister PC;                ///< Program counter (elr_el1).

    u64 padding;

    FpuRegister FpuRegisters[32];  ///< 32 general-purpose NEON registers.

    u32 PState;  ///< pstate & 0xFF0FFE20
    u32 AFSR0;
    u32 AFSR1;
    u32 ESR;

    CpuRegister FAR;  ///< Fault Address Register.
};
void SetUserExceptionHandler(void (*)(UserExceptionInfo*), void*, ulong, UserExceptionInfo*);

// OTHER
void GenerateRandomBytes(void*, u64);
nn::os::Tick GetSystemTick();
nn::os::Tick GetSystemTickFrequency();
u64 GetThreadAvailableCoreMask();
void SetMemoryHeapSize(u64 size);

// Thread-local storage
struct TlsSlot {
    u32 slot;
};
Result AllocateTlsSlot(TlsSlot* slot_out, void (*)(u64));
void FreeTlsSlot(TlsSlot slot);
u64 GetTlsValue(TlsSlot slot);
void SetTlsValue(TlsSlot slot, u64 value);
u32 GetCurrentCoreNumber();

namespace detail {
extern s32 g_CommandLineParameter;
extern char** g_CommandLineParameterArgv;
};  // namespace detail
};  // namespace os
};  // namespace nn
