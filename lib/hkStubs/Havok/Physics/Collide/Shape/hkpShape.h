#pragma once

#include <Havok/Common/Base/Object/hkReferencedObject.h>

class hkShape : public hkReferencedObject {
public:
    virtual hkReal getMaximumProjection(const hkVector4& direction) const;
};
