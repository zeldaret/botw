#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Havok/Physics2012/Collide/Shape/hkpShape.h>

class hkpHeightFieldShape : public hkpShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpHeightFieldShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::HEIGHT_FIELD)

    struct CollideSpheresInput {
        HK_DECLARE_CLASS_ALLOCATOR(CollideSpheresInput)

        hkSphere* m_spheres;
        int m_numSpheres;
        hkReal m_tolerance;
    };

    using SphereCollisionOutput = hkVector4;

    struct hkpSphereCastInput : public hkpShapeRayCastInput {
        HK_DECLARE_CLASS_ALLOCATOR(hkpSphereCastInput)

        hkReal m_radius;
        hkReal m_maxExtraPenetration;
    };

    explicit hkpHeightFieldShape(ShapeType type) : hkpShape(type) {}

    explicit hkpHeightFieldShape(hkFinishLoadedObjectFlag flag) : hkpShape(flag) {
        setType(HKCD_SHAPE_TYPE_FROM_CLASS(hkpHeightFieldShape));
    }

    virtual void collideSpheres(const CollideSpheresInput& input,
                                SphereCollisionOutput* outputArray) const = 0;
    virtual void castSphere(const hkpSphereCastInput& input, const hkpCdBody& cdBody,
                            hkpRayHitCollector& collector) const = 0;
};
