#pragma once

#include <new>

#include "basis/seadRawPrint.h"
#include "basis/seadTypes.h"

namespace sead
{
class FreeList
{
public:
    void setWork(void* work, s32 elem_size, s32 num);
    void reset();

    void* alloc();
    void free(void* ptr);

    void* getFree() const { return mFree; }
    void* work() const { return mWork; }

    static const size_t cPtrSize = sizeof(void*);

private:
    struct Node
    {
        Node* nextFree;
    };

    Node* mFree = nullptr;
    void* mWork = nullptr;
};

inline void FreeList::setWork(void* work, s32 elem_size, s32 num)
{
    SEAD_ASSERT(work);
    SEAD_ASSERT(elem_size > 0 && elem_size % cPtrSize == 0);
    SEAD_ASSERT(num > 0);

    const s32 idx_multiplier = elem_size / cPtrSize;
    void** const ptrs = new (work) void*[num * idx_multiplier];

    mFree = new (work) Node;

    // Create the linked list.
    for (s32 i = 0; i < num - 1; ++i)
        new (&ptrs[i * idx_multiplier]) Node{new (&ptrs[(i + 1) * idx_multiplier]) Node};

    new (&ptrs[(num - 1) * idx_multiplier]) Node{nullptr};

    mWork = work;
}

inline void FreeList::reset()
{
    mFree = nullptr;
    mWork = nullptr;
}

inline void* FreeList::alloc()
{
    if (!mFree)
        return nullptr;

    void* ptr = mFree;
    mFree = mFree->nextFree;
    return ptr;
}

inline void FreeList::free(void* ptr)
{
    mFree = new (ptr) Node{mFree};
}
}  // namespace sead
