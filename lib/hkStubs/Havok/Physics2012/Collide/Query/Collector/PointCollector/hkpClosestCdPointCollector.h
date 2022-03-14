#pragma once

#include <Havok/Physics2012/Collide/Agent/Query/hkpCdPointCollector.h>
#include <Havok/Physics2012/Collide/Query/Collector/PointCollector/hkpRootCdPoint.h>

class hkpClosestCdPointCollector : public hkpCdPointCollector {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpClosestCdPointCollector)

    inline hkpClosestCdPointCollector();
    inline ~hkpClosestCdPointCollector() override;

    inline void reset() override;

    inline hkBool hasHit() const;
    inline const hkpRootCdPoint& getHit() const;
    inline const hkContactPoint& getHitContact() const;

    inline const hkVector4& getUnweldedNormal() const;

protected:
    void addCdPoint(const hkpCdPoint& pointInfo) override;

    hkpRootCdPoint m_hitPoint;
    hkVector4 m_unweldedNormal;
};

inline hkpClosestCdPointCollector::hkpClosestCdPointCollector() {
    reset();
}

inline hkpClosestCdPointCollector::~hkpClosestCdPointCollector() = default;

inline void hkpClosestCdPointCollector::reset() {
    m_hitPoint.m_rootCollidableA = nullptr;
    m_hitPoint.m_contact.setDistanceSimdReal(hkSimdReal::getConstant<HK_QUADREAL_MAX>());
    hkpCdPointCollector::reset();
}

inline hkBool hkpClosestCdPointCollector::hasHit() const {
    return m_hitPoint.m_rootCollidableA != nullptr;
}

inline const hkpRootCdPoint& hkpClosestCdPointCollector::getHit() const {
    return m_hitPoint;
}

inline const hkContactPoint& hkpClosestCdPointCollector::getHitContact() const {
    return m_hitPoint.getContact();
}

inline const hkVector4& hkpClosestCdPointCollector::getUnweldedNormal() const {
    return m_unweldedNormal;
}
