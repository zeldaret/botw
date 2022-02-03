#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeBase.h>

class hkpCdBody;
struct hkpShapeRayCastCollectorOutput;

class hkpRayHitCollector {
public:
    inline hkpRayHitCollector();

    virtual void addRayHit(const hkpCdBody& cdBody,
                           const hkpShapeRayCastCollectorOutput& hitInfo) = 0;

    inline void reset();

    virtual ~hkpRayHitCollector() = default;

    static int shapeKeysFromCdBody(hkpShapeKey* buf, int maxKeys, const hkpCdBody& body);

    hkReal m_earlyOutHitFraction;
};

inline hkpRayHitCollector::hkpRayHitCollector() {
    reset();
}

inline void hkpRayHitCollector::reset() {
    m_earlyOutHitFraction = 1.f;
}
