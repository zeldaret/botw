#pragma once

#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Object/hkReferencedObject.h>

class hkpSimulationIsland;
class hkpWorld;

class hkWorldMemoryAvailableWatchDog : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkWorldMemoryAvailableWatchDog)

    struct MemUsageInfo {
        HK_DECLARE_CLASS_ALLOCATOR(MemUsageInfo)

        int m_maxRuntimeBlockSize;
        int m_sumRuntimeBlockSize;
        hkpSimulationIsland* m_largestSimulationIsland;
    };

    inline hkWorldMemoryAvailableWatchDog() = default;
    inline explicit hkWorldMemoryAvailableWatchDog(hkFinishLoadedObjectFlag flag)
        : hkReferencedObject(flag) {}

    virtual hkInt32 getAmountOfFreeHeapMemoryRequested() = 0;
    virtual void freeHeapMemoryTillRequestedAmountIsAvailable(hkpWorld* world) = 0;
    virtual void reduceConstraintsInIsland(const MemUsageInfo& info, int numIterations) = 0;
};
