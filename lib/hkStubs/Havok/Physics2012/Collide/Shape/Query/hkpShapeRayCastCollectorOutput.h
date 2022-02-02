#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkpShapeRayCastCollectorOutput {
    HK_DECLARE_CLASS_ALLOCATOR(hkpShapeRayCastCollectorOutput)

    inline hkpShapeRayCastCollectorOutput();

    inline hkBool hasHit() const;

    inline void reset();

    hkVector4 m_normal;
    hkReal m_hitFraction;
    int m_extraInfo;
    int m_pad[2];
};

inline hkpShapeRayCastCollectorOutput::hkpShapeRayCastCollectorOutput() {
    reset();
}

inline hkBool hkpShapeRayCastCollectorOutput::hasHit() const {
    return m_hitFraction < 1.0f;
}

inline void hkpShapeRayCastCollectorOutput::reset() {
    m_hitFraction = 1.0f;
    m_extraInfo = -1;
}
