#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkMallocAllocator : public hkMemoryAllocator {
public:
    explicit hkMallocAllocator(int align = HK_REAL_ALIGNMENT)
        : m_align(align), m_currentUsed(0), m_peakUse(0) {}

    void* blockAlloc(int numBytes) override;
    void blockFree(void* p, int numBytes) override;

    void getMemoryStatistics(hkMemoryAllocator::MemoryStatistics& u) const override;
    int getAllocatedSize(const void* obj, int nbytes) const override;
    void resetPeakMemoryStatistics() override;

    int m_align;

    static hkMemoryAllocator* m_defaultMallocAllocator;

protected:
    hkUint32 m_unused;
    hkUint32 m_currentUsed;
    hkUint32 m_peakUse;
};
