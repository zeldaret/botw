#include "KingSystem/System/MemoryProfiler.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(MemoryProfiler)

void MemoryProfiler::init(sead::Heap* heap) {
    mHeap = heap;
    _28 = nullptr;
    _30 = nullptr;
}

}  // namespace ksys
