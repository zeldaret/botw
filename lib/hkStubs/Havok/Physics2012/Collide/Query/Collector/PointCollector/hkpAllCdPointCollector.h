#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Agent/Query/hkpCdPointCollector.h>
#include <Havok/Physics2012/Collide/Query/Collector/PointCollector/hkpRootCdPoint.h>

class hkpAllCdPointCollector : public hkpCdPointCollector {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpAllCdPointCollector)

    inline hkpAllCdPointCollector();
    inline ~hkpAllCdPointCollector() override;
    inline void reset() override;

    inline const hkArray<hkpRootCdPoint>& getHits() const;
    inline hkArray<hkpRootCdPoint>& getHits();

    inline int getNumHits() const;
    inline hkBool hasHit() const;

    void sortHits();

    void addCdPoint(const hkpCdPoint& event) override;

protected:
    hkInplaceArray<hkpRootCdPoint, 8> m_hits;
};

inline hkpAllCdPointCollector::hkpAllCdPointCollector() {
    reset();
}

inline hkpAllCdPointCollector::~hkpAllCdPointCollector() = default;

inline void hkpAllCdPointCollector::reset() {
    m_hits.clear();
    hkpCdPointCollector::reset();
}

inline const hkArray<hkpRootCdPoint>& hkpAllCdPointCollector::getHits() const {
    return m_hits;
}

inline hkArray<hkpRootCdPoint>& hkpAllCdPointCollector::getHits() {
    return m_hits;
}

inline int hkpAllCdPointCollector::getNumHits() const {
    return m_hits.getSize();
}

inline hkBool hkpAllCdPointCollector::hasHit() const {
    return getNumHits() > 0;
}
