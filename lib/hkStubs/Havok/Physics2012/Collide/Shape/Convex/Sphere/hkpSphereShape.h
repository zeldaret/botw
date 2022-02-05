#pragma once

#include <Havok/Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

class hkpSphereShape : public hkpConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpSphereShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::SPHERE)

    HK_FORCE_INLINE hkpSphereShape() {}
    explicit hkpSphereShape(hkReal radius);
    explicit hkpSphereShape(hkFinishLoadedObjectFlag flag);

    HK_FORCE_INLINE void getSupportingVertex(hkVector4Parameter direction,
                                             hkcdVertex& supportingVertexOut) const override;
    HK_FORCE_INLINE void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds,
                                                    hkcdVertex* verticesOut) const override;
    HK_FORCE_INLINE void getCentre(hkVector4& centreOut) const override;
    HK_FORCE_INLINE int getNumCollisionSpheres() const override;
    HK_FORCE_INLINE const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const override;
    HK_FORCE_INLINE void getAabb(const hkTransform& localToWorld, hkReal tolerance,
                                 hkAabb& out) const override;
    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override;
    hkVector4Comparison castRayBundle(const hkpShapeRayBundleCastInput& input,
                                      hkpShapeRayBundleCastOutput& results,
                                      hkVector4ComparisonParameter mask) const override;
    void getFirstVertex(hkVector4& v) const override;

private:
    hkUint32 m_pad16[3];
};
