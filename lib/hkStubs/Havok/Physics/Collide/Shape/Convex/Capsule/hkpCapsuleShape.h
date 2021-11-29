#pragma once

#include "Havok/Common/Base/hkBase.h"

class hkpShape {
public:
    hkpShape();
    virtual ~hkpShape();

    hkUchar filler[0x8];
    hkUint64 m_type;
    hkUchar filler2[0x30];
};

class hkpCapsuleShape : public hkpShape {
public:
    hkpCapsuleShape(const hkVector4& vertexA, const hkVector4& vertexB, hkReal radius);
    virtual ~hkpCapsuleShape();
};
