#include "gsys/gsysMemBuffer.h"

#include <basis/seadNew.h>
#include <heap/seadHeapMgr.h>
#include <math/seadMathCalcCommon.h>

namespace gsys {

MemBuffer::MemBuffer() = default;
MemBuffer::~MemBuffer() = default;

void MemBuffer::tryAlloc(sead::Heap* heap, size_t size, u32 align) {
    if (!heap)
        heap = sead::HeapMgr::sInstancePtr->getCurrentHeap();
    void* buffer = heap->tryAlloc(size, static_cast<s32>(align));
    mSize = size;
    mOffset = 0;
    mBuffer = buffer;
}

void* MemBuffer::alloc(size_t size, u32 align) {
    uintptr_t current = mOffset + reinterpret_cast<uintptr_t>(mBuffer);
    uintptr_t aligned = sead::MathSizeT::roundUp(current, align);
    mOffset += aligned - current + size;
    return reinterpret_cast<void*>(aligned);
}

void MemBuffer::free() {
    delete static_cast<u8*>(mBuffer);
}

}  // namespace gsys