#pragma once

#include <Havok/Physics2012/Collide/Shape/HeightField/hkpHeightFieldShape.h>

class hkpPlaneShape : public hkpHeightFieldShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpPlaneShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::PLANE)

    hkpPlaneShape(const hkVector4& plane, const hkAabb& aabb);

    hkpPlaneShape(const hkVector4& direction, const hkVector4& center,
                  const hkVector4& halfExtents);

    explicit hkpPlaneShape(hkFinishLoadedObjectFlag flag);

    const hkVector4& getPlane() const { return m_plane; }
    const hkVector4& getAabbCenter() const { return m_aabbCenter; }
    const hkVector4& getAabbHalfExtents() const { return m_aabbHalfExtents; }

    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;
    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override;
    void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                              hkpRayHitCollector& collector) const override;
    void castSphere(const hkpSphereCastInput& input, const hkpCdBody& cdBody,
                    hkpRayHitCollector& collector) const override;
    void collideSpheres(const CollideSpheresInput& input,
                        SphereCollisionOutput* outputArray) const override;

protected:
    hkVector4 m_plane;
    hkVector4 m_aabbCenter;
    hkVector4 m_aabbHalfExtents;
};
