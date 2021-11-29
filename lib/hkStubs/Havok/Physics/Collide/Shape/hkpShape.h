#pragma once

#include <Havok/Common/Base/Object/hkReferencedObject.h>

class hkpShape : public hkReferencedObject {
public:
    virtual ~hkpShape();

    virtual hkReal getMaximumProjection(const hkVector4& direction) const;

    hkUchar filler[0x8];
    hkUint64 m_type;
    hkUchar filler2[0x30];
};
