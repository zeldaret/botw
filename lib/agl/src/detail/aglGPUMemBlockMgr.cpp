#include "agl/detail/aglGPUMemBlockMgr.h"

namespace agl::detail {
const MemoryPoolType MemoryPoolType::cInvalidPoolType(0);
const MemoryPoolType MemoryPoolType::cValidPoolType(VALID_POOL_TYPE_VALUE);

SEAD_SINGLETON_DISPOSER_IMPL(GPUMemBlockMgr)

GPUMemBlockMgr::GPUMemBlockMgr() {
    mMinBlockSize = cGPUPhysicalMemorySizeAlignment;
    mFlags = GPUMemBlockMgrFlags::EnablePoolSharing;
}

GPUMemBlockMgr::~GPUMemBlockMgr() {
    mMngrHeaps.freeBuffer();
}

void GPUMemBlockMgr::initialize(sead::Heap* heap1, sead::Heap* heap2) {
    mMngrHeaps.allocBuffer(0x1000, heap1);
    mMngrHeaps.clear();
}

void GPUMemBlockMgr::enableSharedMemoryPool(bool enabled) {
    mFlags.change(GPUMemBlockMgrFlags::EnablePoolSharing, enabled);
}

u64 GPUMemBlockMgr::calcGPUMemorySize(u64 userSize) {
    return sead::MathSizeT::roundUp(userSize, cGPUPhysicalMemorySizeAlignment);
}

s32 GPUMemBlockMgr::calcGPUMemoryAlignment(s32 userAlignment) {
    return sead::Mathi::roundUpPow2(sead::Mathi::abs(userAlignment),
                                    cGPUPhysicalMemorySizeAlignment) *
           sead::Mathi::sign(userAlignment);
}

GPUMemBlockMgrHeapEx* GPUMemBlockMgr::findGPUMemBlockMgrHeapEx_(sead::Heap* p_heap,
                                                                int* p_outIndex) {
    SEAD_ASSERT(p_heap != nullptr);

    if (mMngrHeaps.isEmpty()) {
        return nullptr;
    }

    // TODO
    return nullptr;
}

GPUMemBlockMgrHeapEx::GPUMemBlockMgrHeapEx(sead::Heap* p_heap) {
    mAllowSharing = 1;
    m08 = nullptr;
    m10 = nullptr;
}

}  // namespace agl::detail