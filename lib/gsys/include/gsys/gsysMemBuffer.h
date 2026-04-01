#pragma once

#include <basis/seadTypes.h>
#include <heap/seadHeap.h>

namespace gsys {

class MemBuffer {
public:
    MemBuffer();
    virtual ~MemBuffer();

    void* alloc(size_t size, u32 align);
    void tryAlloc(sead::Heap* heap, size_t size, u32 align);
    void free();

private:
    void* mBuffer = nullptr;
    uintptr_t mOffset = 0;
    size_t mSize = 0;
};

}  // namespace gsys