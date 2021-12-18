#pragma once

#include <Havok/Common/Base/hkBase.h>

// FIXME: incomplete. Also this should be inheriting from hkpBase
class hkpShape : public hkReferencedObject {
public:
    virtual ~hkpShape();

    virtual hkReal getMaximumProjection(const hkVector4& direction) const;

    hkUint64 m_type;
    hkUchar filler2[0x30];
};
