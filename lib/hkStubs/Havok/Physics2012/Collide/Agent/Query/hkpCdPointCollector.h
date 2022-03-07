#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkpCdPoint;

class hkpCdPointCollector {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCdPointCollector)

    inline hkpCdPointCollector();
    inline virtual ~hkpCdPointCollector() = default;

    virtual void addCdPoint(const hkpCdPoint& point) = 0;

    inline virtual void reset();

    inline hkReal getEarlyOutDistance() const;

protected:
    hkReal m_earlyOutDistance;
};

inline hkpCdPointCollector::hkpCdPointCollector() {
    reset();
}

inline void hkpCdPointCollector::reset() {
    m_earlyOutDistance = HK_REAL_MAX;
}

inline hkReal hkpCdPointCollector::getEarlyOutDistance() const {
    return m_earlyOutDistance;
}
