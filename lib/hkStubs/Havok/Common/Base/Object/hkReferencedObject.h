#pragma once

#include <Havok/Common/Base/Object/hkBaseObject.h>

class hkReferencedObject : public hkBaseObject {
public:
    virtual ~hkReferencedObject() {}

    virtual const void* getClassType() const;
};
