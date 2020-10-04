#include "KingSystem/Resource/resUnitPool.h"

namespace ksys::res {

ResourceUnitPool::ResourceUnitPool() = default;

ResourceUnitPool::~ResourceUnitPool() = default;

bool ResourceUnitPool::init() {
    for (s32 i = 0; i < UnitCapacity; ++i)
        mRingBuffer.pushBack(&mUnits[i]);
    return true;
}

ResourceUnit* ResourceUnitPool::tryAlloc() {
    if (mRingBuffer.empty())
        return nullptr;
    return mRingBuffer.popFront();
}

ResourceUnit* ResourceUnitPool::alloc() {
    return mRingBuffer.popFront();
}

void ResourceUnitPool::free(ResourceUnit* unit) {
    mRingBuffer.pushBack(unit);
}

void ResourceUnitPool::freeForSync(ResourceUnit* unit) {
    free(unit);
}

}  // namespace ksys::res
