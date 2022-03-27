#pragma once

#include <Havok/Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

namespace sead {
class ExpHeap;
}

namespace ksys::phys {

class HavokMemoryAllocator : public hkMallocAllocator, public sead::hostio::Node {
public:
    explicit HavokMemoryAllocator(int align = HK_REAL_ALIGNMENT);
    ~HavokMemoryAllocator() override;

    void initDualHeap(sead::Heap* heap1, sead::Heap* heap2, u32 size, const sead::SafeString& name);

    void* blockAlloc(int numBytes) override;
    void blockFree(void* p, int numBytes) override;
    int getAllocatedSize(const void* obj, int nbytes) const override;

    size_t getHeapSize() const;
    size_t getHeapFreeSize() const;

private:
    sead::ExpHeap* mHeap{};
};

}  // namespace ksys::phys
