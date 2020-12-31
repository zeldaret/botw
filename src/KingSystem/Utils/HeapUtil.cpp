#include "KingSystem/Utils/HeapUtil.h"
#include <heap/seadHeapMgr.h>
#include <thread/seadThread.h>

namespace ksys::util {

// Name, layout and purpose unknown; this is stubbed in release builds
class DebugHeapHolder {
    SEAD_SINGLETON_DISPOSER(DebugHeapHolder)
    DebugHeapHolder() = default;

public:
    virtual ~DebugHeapHolder() = default;
    virtual sead::Heap* getHeap() { return nullptr; }
};

SEAD_SINGLETON_DISPOSER_IMPL(DebugHeapHolder)

// Name, layout and purpose unknown; this is stubbed in release builds
class DebugHeapHolder2 {
    SEAD_SINGLETON_DISPOSER(DebugHeapHolder2)
    DebugHeapHolder2() = default;

public:
    virtual ~DebugHeapHolder2() = default;
    virtual sead::Heap* getHeap() { return nullptr; }
};

SEAD_SINGLETON_DISPOSER_IMPL(DebugHeapHolder2)

sead::Heap* getHeapOrCurrentHeap(sead::Heap* heap) {
    if (heap)
        return heap;

    if (!sead::ThreadMgr::instance())
        return nullptr;

    return getCurrentHeap();
}

void adjustHeapOrCurrentHeap(sead::Heap* heap) {
    if (!heap)
        heap = getCurrentHeap();
    heap->adjust();
}

sead::Heap* getCurrentHeap() {
    return sead::HeapMgr::instance()->getCurrentHeap();
}

sead::Heap* getDebugHeap() {
    if (!DebugHeapHolder::instance())
        return nullptr;
    return DebugHeapHolder::instance()->getHeap();
}

sead::Heap* getDebugHeap2() {
    if (DebugHeapHolder2::instance())
        return DebugHeapHolder2::instance()->getHeap();
    return getDebugHeap();
}

}  // namespace ksys::util
