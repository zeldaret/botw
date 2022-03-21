#include "basis/seadRawPrint.h"
#include "thread/seadSemaphore.h"

namespace sead
{
Semaphore::Semaphore() = default;

Semaphore::Semaphore(s32 initial_count) : Semaphore()
{
    initialize(initial_count);
}

Semaphore::Semaphore(s32 initial_count, s32 max_count) : Semaphore()
{
    initialize(initial_count, max_count);
}

Semaphore::Semaphore(Heap* heap) : Semaphore(heap, HeapNullOption::UseSpecifiedOrContainHeap) {}

Semaphore::Semaphore(Heap* heap, s32 initial_count) : Semaphore(heap)
{
    initialize(initial_count);
}

Semaphore::Semaphore(Heap* heap, s32 initial_count, s32 max_count) : Semaphore(heap)
{
    initialize(initial_count, max_count);
}

Semaphore::Semaphore(Heap* heap, IDisposer::HeapNullOption heap_null_option)
    : IDisposer(heap, heap_null_option)
{
}

Semaphore::Semaphore(Heap* heap, IDisposer::HeapNullOption heap_null_option, s32 initial_count)
    : Semaphore(heap, heap_null_option)
{
    initialize(initial_count);
}

Semaphore::Semaphore(Heap* heap, IDisposer::HeapNullOption heap_null_option, s32 initial_count,
                     s32 max_count)
    : Semaphore(heap, heap_null_option)
{
    initialize(initial_count, max_count);
}

Semaphore::~Semaphore()
{
    nn::os::FinalizeSemaphore(&mSemaphoreInner);
    setInitialized(false);
}

void Semaphore::initialize(s32 initial_count, s32 max_count)
{
#ifdef SEAD_DEBUG
    SEAD_ASSERT_MSG(!mInitialized, "Semaphore is already initialized.");
#endif
    nn::os::InitializeSemaphore(&mSemaphoreInner, initial_count, max_count);
    setInitialized(true);
}

void Semaphore::lock()
{
#ifdef SEAD_DEBUG
    SEAD_ASSERT_MSG(mInitialized, "Semaphore is not initialized.");
#endif
    nn::os::AcquireSemaphore(&mSemaphoreInner);
}

bool Semaphore::tryLock()
{
#ifdef SEAD_DEBUG
    SEAD_ASSERT_MSG(mInitialized, "Semaphore is not initialized.");
#endif
    return nn::os::TryAcquireSemaphore(&mSemaphoreInner);
}

void Semaphore::unlock()
{
#ifdef SEAD_DEBUG
    SEAD_ASSERT_MSG(mInitialized, "Semaphore is not initialized.");
#endif
    nn::os::ReleaseSemaphore(&mSemaphoreInner);
}
}  // namespace sead
