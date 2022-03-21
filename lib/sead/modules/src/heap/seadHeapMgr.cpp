#include <heap/seadHeap.h>
#include <heap/seadHeapMgr.h>

namespace sead
{
HeapMgr* HeapMgr::sInstancePtr = NULL;

HeapMgr HeapMgr::sInstance;
Arena HeapMgr::sDefaultArena;
HeapMgr::RootHeaps HeapMgr::sRootHeaps;
HeapMgr::IndependentHeaps HeapMgr::sIndependentHeaps;
CriticalSection HeapMgr::sHeapTreeLockCS;

HeapMgr::HeapMgr() : mAllocFailedCallback(NULL) {}

Heap* HeapMgr::findContainHeap(const void* ptr) const
{
    Heap* containHeap;

    sHeapTreeLockCS.lock();

    for (Heap& heap : sRootHeaps)
    {
        containHeap = heap.findContainHeap_(ptr);
        if (containHeap != NULL)
        {
            sHeapTreeLockCS.unlock();
            return containHeap;
        }
    }

    for (Heap& heap : sIndependentHeaps)
    {
        containHeap = heap.findContainHeap_(ptr);
        if (containHeap != NULL)
        {
            sHeapTreeLockCS.unlock();
            return containHeap;
        }
    }

    sHeapTreeLockCS.unlock();
    return NULL;
}

FindContainHeapCache::FindContainHeapCache() = default;

bool FindContainHeapCache::tryRemoveHeap(Heap* heap)
{
    uintptr_t original;
    if (mHeap.compareExchange(uintptr_t(heap), 0, &original))
        return true;
    return (original & ~1u) != uintptr_t(heap);
}
}  // namespace sead
