#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/hkpShape.h>

class hkpSphereRepShape : public hkpShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpSphereRepShape)
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::SPHERE_REP)

    HK_FORCE_INLINE hkpSphereRepShape() = default;
    explicit hkpSphereRepShape(ShapeType type) : hkpShape(type) {}
    explicit hkpSphereRepShape(hkFinishLoadedObjectFlag flag) : hkpShape(flag) {
        setType(HKCD_SHAPE_TYPE_FROM_CLASS(hkpSphereRepShape));
    }
};
