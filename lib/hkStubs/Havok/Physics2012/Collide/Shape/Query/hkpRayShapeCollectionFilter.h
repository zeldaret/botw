#pragma once

#include <Havok/Common/Base/Types/hkBaseTypes.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeBase.h>

class hkpShapeRayCastInput;
class hkpShapeContainer;

class hkpRayShapeCollectionFilter {
public:
    virtual hkBool isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                                      const hkpShapeContainer& bContainer,
                                      hkpShapeKey bKey) const = 0;

    virtual ~hkpRayShapeCollectionFilter() = default;
};
