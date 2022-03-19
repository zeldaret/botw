#pragma once

#include <Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastOutput.h>

class hkpCollidable;

struct hkpWorldRayCastOutput : public hkpShapeRayCastOutput {
    HK_DECLARE_CLASS_ALLOCATOR(hkpWorldRayCastOutput)

    inline hkBool hasHit() const;

    inline hkBool operator<(const hkpWorldRayCastOutput& b) const;

    inline void reset();

    const hkpCollidable* m_rootCollidable = nullptr;
};

inline hkBool hkpWorldRayCastOutput::hasHit() const {
    return m_rootCollidable != nullptr;
}

inline hkBool hkpWorldRayCastOutput::operator<(const hkpWorldRayCastOutput& b) const {
    return m_hitFraction < b.m_hitFraction;
}

inline void hkpWorldRayCastOutput::reset() {
    m_rootCollidable = nullptr;
    hkpShapeRayCastOutput::reset();
}
