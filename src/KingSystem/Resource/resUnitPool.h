#pragma once

#include <container/seadRingBuffer.h>
#include "KingSystem/Resource/resUnit.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class ResourceUnitPool {
public:
    ResourceUnitPool();
    virtual ~ResourceUnitPool();

    ResourceUnitPool(const ResourceUnitPool&) = delete;
    ResourceUnitPool& operator=(const ResourceUnitPool&) = delete;

    bool init();

    ResourceUnit* tryAlloc();
    ResourceUnit* alloc();

    void free(ResourceUnit* unit);
    void freeForSync(ResourceUnit* unit);

private:
    static constexpr s32 UnitCapacity = 9000;

    ResourceUnit mUnits[UnitCapacity];
    sead::FixedRingBuffer<ResourceUnit*, UnitCapacity> mRingBuffer;
};
KSYS_CHECK_SIZE_NX150(ResourceUnitPool, 0x9c01a0);

}  // namespace ksys::res
