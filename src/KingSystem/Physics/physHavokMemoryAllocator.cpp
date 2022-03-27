#include "KingSystem/Physics/physHavokMemoryAllocator.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::phys {

HavokMemoryAllocator::HavokMemoryAllocator(int align) : hkMallocAllocator(align) {}

HavokMemoryAllocator::~HavokMemoryAllocator() = default;

void HavokMemoryAllocator::initDualHeap(sead::Heap* heap1, sead::Heap* heap2, u32 size,
                                        const sead::SafeString& name) {
    mHeap = util::DualHeap::create(size, name, heap1, heap2, alignof(void*),
                                   sead::Heap::cHeapDirection_Forward, true);
}

void* HavokMemoryAllocator::blockAlloc(int numBytes) {
    return mHeap->tryAlloc(numBytes, m_align);
}

void HavokMemoryAllocator::blockFree(void* p, int numBytes) {
    mHeap->free(p);
}

size_t HavokMemoryAllocator::getHeapSize() const {
    return mHeap->getSize();
}

size_t HavokMemoryAllocator::getHeapFreeSize() const {
    return sead::DynamicCast<util::DualHeap>(mHeap)->getFreeSize();
}

int HavokMemoryAllocator::getAllocatedSize(const void* obj, int nbytes) const {
    // sead::ExpHeap::getAllocatedSize isn't const-correct :/
    return static_cast<int>(mHeap->getAllocatedSize(const_cast<void*>(obj)));
}

}  // namespace ksys::phys
