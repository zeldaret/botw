#include "KingSystem/Utils/HeapUtil.h"
#include <heap/seadHeapMgr.h>
#include <thread/seadThread.h>

namespace ksys::util {

sead::Heap* getHeapOrCurrentHeap(sead::Heap* heap) {
    if (heap)
        return heap;

    if (!sead::ThreadMgr::instance())
        return nullptr;

    return sead::HeapMgr::instance()->getCurrentHeap();
}

}  // namespace ksys::util
