#include "KingSystem/Event/evtEventResource.h"
#include <heap/seadHeap.h>

namespace ksys::evt {

void* eventFlowAlloc(size_t size, size_t alignment, void* userdata) {
    auto* heap = static_cast<sead::Heap*>(userdata);
    if (!heap)
        return nullptr;
    return heap->tryAlloc(size, static_cast<int>(alignment));
}

void eventFlowFree(void* ptr, void* userdata) {
    auto* heap = static_cast<sead::Heap*>(userdata);
    if (heap)
        heap->free(ptr);
}

}  // namespace ksys::evt
