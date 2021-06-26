#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class MemoryProfiler {
    SEAD_SINGLETON_DISPOSER(MemoryProfiler)
    MemoryProfiler() = default;

public:
    void init(sead::Heap* heap);

    sead::Heap* mHeap{};
    void* _28{};
    void* _30{};
};
KSYS_CHECK_SIZE_NX150(MemoryProfiler, 0x38);

}  // namespace ksys
