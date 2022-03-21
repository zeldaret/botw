#include "agl/Utils/aglAtomicPtrArray.h"
#include <algorithm>
#include <basis/seadNew.h>

namespace agl::detail {

void AtomicPtrArrayImpl::setBuffer(s32 ptrNumMax, void* buf) {
    if (ptrNumMax >= 1) {
        if (!buf) {
            SEAD_ASSERT_MSG(false, "buf is null");
            return;
        }

        mPtrs = static_cast<void**>(buf);
        mPtrNum = 0;
        mPtrNumMax = ptrNumMax;
    } else {
        SEAD_ASSERT_MSG(false, "ptrNumMax[%d] must be larger than zero", ptrNumMax);
    }
}

void AtomicPtrArrayImpl::allocBuffer(s32 ptrNumMax, sead::Heap* heap, s32 alignment) {
    SEAD_ASSERT(mPtrs == nullptr);

    if (ptrNumMax >= 1)
        setBuffer(ptrNumMax, new (heap, alignment) u8[s32(sizeof(void*)) * ptrNumMax]);
    else
        SEAD_ASSERT_MSG(false, "ptrNumMax[%d] must be larger than zero", ptrNumMax);
}

void AtomicPtrArrayImpl::freeBuffer() {
    if (isBufferReady()) {
        delete[] mPtrs;
        mPtrs = nullptr;
        mPtrNum = 0;
        mPtrNumMax = 0;
    }
}

void AtomicPtrArrayImpl::erase(s32 pos, s32 count) {
    if (pos < 0) {
        SEAD_ASSERT_MSG(false, "illegal position[%d]", pos);
        return;
    }

    if (count < 0) {
        SEAD_ASSERT_MSG(false, "illegal number[%d]", count);
        return;
    }

    const s32 end_pos = pos + count;
    const s32 ptr_num = mPtrNum;

    if (pos + count > ptr_num) {
        SEAD_ASSERT_MSG(false, "pos[%d] + num[%d] exceed size[%d]", pos, count, ptr_num);
        return;
    }

    if (ptr_num > end_pos)
        sead::MemUtil::copyOverlap(mPtrs + pos, mPtrs + end_pos,
                                   sizeof(void*) * (ptr_num - end_pos));

    mPtrNum = ptr_num - count;
}

// NON_MATCHING: semantically equivalent (Fisher–Yates)
void AtomicPtrArrayImpl::shuffle(sead::Random* random) {
    SEAD_ASSERT(random);
    for (s32 i = mPtrNum - 1; i > 0; --i)
        swap(i, random->getS32Range(0, i + 1));
}

// NON_MATCHING: Nintendo implemented a sorting algorithm manually
void AtomicPtrArrayImpl::sort(CompareCallbackImpl cmp) {
    std::sort(mPtrs, mPtrs + mPtrNum, [cmp](void* a, void* b) { return cmp(a, b) < 0; });
}

// NON_MATCHING: Nintendo implemented heap sort manually
void AtomicPtrArrayImpl::heapSort(CompareCallbackImpl cmp) {
    std::make_heap(mPtrs, mPtrs + mPtrNum);
    std::sort_heap(mPtrs, mPtrs + mPtrNum, [cmp](void* a, void* b) { return cmp(a, b) < 0; });
}

}  // namespace agl::detail
