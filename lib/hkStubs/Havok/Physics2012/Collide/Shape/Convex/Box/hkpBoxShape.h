#pragma once

#include <Havok/Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

/// A simple box shape centered around the origin.
class hkpBoxShape : public hkpConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpBoxShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::BOX)

public:
    hkpBoxShape() {}
    explicit hkpBoxShape(const hkVector4& halfExtents, hkReal radius = hkConvexShapeDefaultRadius);
    explicit hkpBoxShape(hkFinishLoadedObjectFlag flag);

    ~hkpBoxShape() override;

    void getSupportingVertex(hkVector4Parameter direction,
                             hkcdVertex& supportingVertexOut) const override;
    void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds,
                                    hkcdVertex* verticesOut) const override;
    void getCentre(hkVector4& centreOut) const override;
    int getNumCollisionSpheres() const override;
    const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const override;
    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;
    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override;
    void getFirstVertex(hkVector4& v) const override;

    inline const hkVector4& getHalfExtents() const;
    void setHalfExtents(const hkVector4& halfExtents);

protected:
    hkVector4 m_halfExtents;
};

inline int hkpBoxShape::getNumCollisionSpheres() const {
    return 0;
}

inline const hkVector4& hkpBoxShape::getHalfExtents() const {
    return m_halfExtents;
}
