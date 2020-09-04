#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}

namespace ksys::util {

/// Returns the specified heap if it is not null. Otherwise, this returns the current heap.
sead::Heap* getHeapOrCurrentHeap(sead::Heap* heap);

}  // namespace ksys::util
