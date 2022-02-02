#pragma once

#include <Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastCollectorOutput.h>
#include <Havok/Physics2012/Collide/Shape/hkpShape.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeBase.h>

struct hkpShapeRayCastOutput : public hkpShapeRayCastCollectorOutput {
    HK_DECLARE_CLASS_ALLOCATOR(hkpShapeRayCastOutput)

    static constexpr int MAX_HIERARCHY_DEPTH = 8;

    HK_FORCE_INLINE hkpShapeRayCastOutput();

    HK_FORCE_INLINE void changeLevel(int delta);
    HK_FORCE_INLINE void setKey(hkpShapeKey key);
    HK_FORCE_INLINE int getLevel() const;

    HK_FORCE_INLINE void reset();

    hkpShapeKey m_shapeKeys[MAX_HIERARCHY_DEPTH];

private:
    HK_FORCE_INLINE void _reset();

    int m_shapeKeyIndex;
};

inline hkpShapeRayCastOutput::hkpShapeRayCastOutput() {
    _reset();
}

inline void hkpShapeRayCastOutput::changeLevel(int delta) {
    m_shapeKeyIndex += delta;
}

inline void hkpShapeRayCastOutput::setKey(hkpShapeKey key) {
    m_shapeKeys[m_shapeKeyIndex] = key;
}

inline int hkpShapeRayCastOutput::getLevel() const {
    return m_shapeKeyIndex;
}

inline void hkpShapeRayCastOutput::reset() {
    hkpShapeRayCastCollectorOutput::reset();
    _reset();
}

inline void hkpShapeRayCastOutput::_reset() {
    m_shapeKeyIndex = 0;
    m_shapeKeys[0] = HK_INVALID_SHAPE_KEY;
}
