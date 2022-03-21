#include <thread/seadCriticalSection.h>

namespace sead
{
CriticalSection::CriticalSection() : IDisposer(), mCriticalSectionInner()
{
    OSInitMutex(&mCriticalSectionInner);
}

CriticalSection::CriticalSection(Heap* disposer_heap)
    : IDisposer(disposer_heap, HeapNullOption::UseSpecifiedOrContainHeap)
{
    OSInitMutex(&mCriticalSectionInner);
}

CriticalSection::CriticalSection(Heap* disposer_heap, HeapNullOption heap_null_option)
    : IDisposer(disposer_heap, heap_null_option)
{
    OSInitMutex(&mCriticalSectionInner);
}

CriticalSection::~CriticalSection() {}

void CriticalSection::lock()
{
    OSLockMutex(&mCriticalSectionInner);
}

bool CriticalSection::tryLock()
{
    return OSTryLockMutex(&mCriticalSectionInner);
}

void CriticalSection::unlock()
{
    OSUnlockMutex(&mCriticalSectionInner);
}
}  // namespace sead
