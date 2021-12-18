#pragma once

#include <Havok/Physics2012/Dynamics/World/Memory/hkpWorldMemoryAvailableWatchDog.h>

class hkpDefaultWorldMemoryWatchDog : public hkWorldMemoryAvailableWatchDog {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpDefaultWorldMemoryWatchDog)

    explicit hkpDefaultWorldMemoryWatchDog(hkInt32 freeHeapMemoryRequested = 20000);

    explicit hkpDefaultWorldMemoryWatchDog(hkFinishLoadedObjectFlag flag)
        : hkWorldMemoryAvailableWatchDog(flag) {}

    hkInt32 getAmountOfFreeHeapMemoryRequested() override;
    void freeHeapMemoryTillRequestedAmountIsAvailable(hkpWorld* world) override;
    void reduceConstraintsInIsland(const MemUsageInfo& info, int numIterations) override;

protected:
    static void removeObjectsFromIsland(hkpSimulationIsland* island,
                                        int minAutoRemoveLevelToProcess,
                                        hkInt32 freeHeapMemoryRequested,
                                        int& maxFoundAutoRemoveLevelOut);

    hkInt32 m_freeHeapMemoryRequested;
};
