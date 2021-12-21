#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeBase.h>

#define HK_INVALID_SHAPE_KEY 0xffffffff
#define HK_INVALID_VERTEX_ID 0xffff

// FIXME: incomplete.
class hkpShape : public hkpShapeBase {
public:
    virtual ~hkpShape();

    virtual hkReal getMaximumProjection(const hkVector4& direction) const;

    hkUint64 m_type;
    hkUchar filler2[0x30];
};
