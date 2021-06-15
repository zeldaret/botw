#include "KingSystem/ActorSystem/actBaseProcHeapMgr.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(BaseProcHeapMgr)

BaseProcHeapMgr::BaseProcHeapMgr() = default;

BaseProcHeapMgr::~BaseProcHeapMgr() = default;

sead::Heap* BaseProcHeapMgr::getHeap() const {
    return mHeap;
}

void BaseProcHeapMgr::setHeap(sead::Heap* heap) {
    mHeap = heap;
}

}  // namespace ksys::act
