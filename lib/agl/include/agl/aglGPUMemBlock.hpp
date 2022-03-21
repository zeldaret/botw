#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "aglGPUCommon.hpp"

namespace agl {

namespace detail {
class MemoryPool;
class MemoryPoolHeap;
}  // namespace detail

class GPUMemBlockBase {
public:
    explicit GPUMemBlockBase(sead::Heap* p_heap);
    virtual ~GPUMemBlockBase();

    void clear();
    void freeBuffer();
    void free();
    void allocBuffer_(u64, sead::Heap*, s32, MemoryAttribute);
    bool tryAllocBuffer_(u64, sead::Heap*, s32, MemoryAttribute);
    void setBuffer_(u64, void*, void*, MemoryAttribute);
    void setVirtual_(u64, sead::Heap*, MemoryAttribute, GPUMemVoidAddr, s32);
    void addList(GPUMemBlockBase*);
    void setMemoryPool(void*, u64, detail::MemoryPool*);
    void setMemoryPoolHeap(void*, u64, detail::MemoryPoolHeap*);
    u64 getByteOffset() const;
    u64 getMemoryPoolType() const;

    // TODO: the rest of the methods...

private:
    void* mMemoryBuffer;
    u64 mMemoryBufferSize;
    detail::MemoryPool* mpMemoryPool;
    detail::MemoryPoolHeap* mMemoryPoolHeap;
    uint8_t mFlags;
    GPUMemBlockBase* mpTail;
};

static_assert(sizeof(GPUMemBlockBase) == 0x38);

}  // namespace agl
