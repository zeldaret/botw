#pragma once

#include <basis/seadTypes.h>
#include <evfl/EvflAllocator.h>

namespace sead {
class Heap;

}
namespace ksys::evt {

// TODO
class EventResource {};

void* eventFlowAlloc(size_t size, size_t alignment, void* userdata);
void eventFlowFree(void* ptr, void* userdata);

inline evfl::AllocateArg makeEvflAllocateArg(sead::Heap* heap) {
    evfl::AllocateArg arg{};
    arg.alloc = eventFlowAlloc;
    arg.free = eventFlowFree;
    arg.alloc_userdata = heap;
    arg.free_userdata = heap;
    return arg;
}

}  // namespace ksys::evt
