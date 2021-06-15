#pragma once

#include <heap/seadDisposer.h>

namespace ksys::act {

class BaseProcHeapMgr {
    SEAD_SINGLETON_DISPOSER(BaseProcHeapMgr)
    BaseProcHeapMgr();
    virtual ~BaseProcHeapMgr();

public:
    sead::Heap* getHeap() const;
    void setHeap(sead::Heap* heap);

private:
    sead::Heap* mHeap{};
    u32 _30{};
};

}  // namespace ksys::act
