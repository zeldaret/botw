#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}

namespace ksys::util {

/// Returns the specified heap if it is not null. Otherwise, this returns the current heap.
sead::Heap* getHeapOrCurrentHeap(sead::Heap* heap);

void adjustHeapOrCurrentHeap(sead::Heap* heap);

sead::Heap* getCurrentHeap();
sead::Heap* getDebugHeap();
sead::Heap* getDebugHeap2();

}  // namespace ksys::util
