#include "thread/seadCriticalSection.h"

namespace sead
{
CriticalSection::CriticalSection() : IDisposer()
{
    nn::os::InitializeMutex(&mCriticalSectionInner, true, 0);
}

CriticalSection::CriticalSection(Heap* disposer_heap)
    : IDisposer(disposer_heap, HeapNullOption::UseSpecifiedOrContainHeap)
{
    nn::os::InitializeMutex(&mCriticalSectionInner, true, 0);
}

CriticalSection::CriticalSection(Heap* disposer_heap, HeapNullOption heap_null_option)
    : IDisposer(disposer_heap, heap_null_option)
{
    nn::os::InitializeMutex(&mCriticalSectionInner, true, 0);
}

CriticalSection::~CriticalSection()
{
    nn::os::FinalizeMutex(&mCriticalSectionInner);
}

void CriticalSection::lock()
{
    nn::os::LockMutex(&mCriticalSectionInner);
}

bool CriticalSection::tryLock()
{
    return nn::os::TryLockMutex(&mCriticalSectionInner);
}

void CriticalSection::unlock()
{
    nn::os::UnlockMutex(&mCriticalSectionInner);
}
}  // namespace sead
