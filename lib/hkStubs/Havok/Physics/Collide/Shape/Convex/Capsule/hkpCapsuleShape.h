#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics/Collide/Shape/hkpShape.h>

class hkpCapsuleShape : public hkpShape {
public:
    hkpCapsuleShape(const hkVector4& vertexA, const hkVector4& vertexB, hkReal radius);
    virtual ~hkpCapsuleShape();
};
