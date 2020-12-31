#pragma once

#include <heap/seadDisposer.h>

namespace ksys::act {

class ActorHeapUtil {
    SEAD_SINGLETON_DISPOSER(ActorHeapUtil)
    ActorHeapUtil() = default;
    virtual ~ActorHeapUtil();

public:
    sead::Heap* getBaseProcHeap() const { return mBaseProcHeap; }
    void setBaseProcHeap(sead::Heap* heap) { mBaseProcHeap = heap; }

    sead::Heap* getMemoryResidentActorHeap() const { return mMemoryResidentActorHeap; }
    void setMemoryResidentActorHeap(sead::Heap* heap) { mMemoryResidentActorHeap = heap; }

private:
    // "uking::Stage::ForBaseProcDual"
    sead::Heap* mBaseProcHeap{};
    sead::Heap* mMemoryResidentActorHeap{};
};

}  // namespace ksys::act
