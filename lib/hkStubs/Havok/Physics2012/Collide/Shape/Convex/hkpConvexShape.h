#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/HeightField/hkpSphereRepShape.h>
#include <Havok/Physics2012/Collide/Shape/hkpShape.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeContainer.h>

extern hkReal hkConvexShapeDefaultRadius;

class hkpConvexShape : public hkpSphereRepShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpConvexShape)
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::CONVEX)

    using VertexId = hkpVertexId;

    enum WeldResult {
        WELD_RESULT_REJECT_CONTACT_POINT,
        WELD_RESULT_ACCEPT_CONTACT_POINT_MODIFIED,
        WELD_RESULT_ACCEPT_CONTACT_POINT_UNMODIFIED
    };

    HK_FORCE_INLINE hkpConvexShape() = default;
    hkpConvexShape(hkFinishLoadedObjectFlag flag);

    void getCentre(hkVector4& centreOut) const override;
    int weldContactPoint(hkpVertexId* featurePoints, hkUint8& numFeaturePoints,
                         hkVector4& contactPointWs, const hkTransform* thisObjTransform,
                         const hkpConvexShape* collidingShape,
                         const hkTransform* collidingTransform,
                         hkVector4& separatingNormalInOut) const override;
    void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                              hkpRayHitCollector& collector) const override;
    virtual void getFirstVertex(hkVector4& v) const = 0;
    bool isConvex() const override { return true; }
    hkReal getMaximumProjection(const hkVector4& direction) const override;
    virtual int getSize() const { return 0; }

    inline const hkReal& getRadius() const;
    inline void setRadius(hkReal radius);
    inline void setRadiusUnchecked(hkReal radius);

protected:
    inline hkpConvexShape(ShapeType type, hkReal radius) : hkpSphereRepShape(type) {
        m_radius = radius;
    }

    hkReal m_radius;
};

class hkpConvexTransformShapeBase : public hkpConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpConvexTransformShapeBase)
    HK_DECLARE_REFLECTION()

public:
    hkpConvexTransformShapeBase() {}

    explicit hkpConvexTransformShapeBase(hkFinishLoadedObjectFlag flag)
        : hkpConvexShape(flag), m_childShape(flag) {}

protected:
    hkpConvexTransformShapeBase(ShapeType type, hkReal radius, const hkpConvexShape* childShape,
                                hkpShapeContainer::ReferencePolicy ref);
    void getChildShapeFromPpu(int thisShapeSize) const;

    hkpSingleShapeContainer m_childShape;
    mutable int m_childShapeSizeForSpu;
};

inline const hkReal& hkpConvexShape::getRadius() const {
    return m_radius;
}

inline void hkpConvexShape::setRadius(hkReal radius) {
    setRadiusUnchecked(radius);
}

inline void hkpConvexShape::setRadiusUnchecked(hkReal radius) {
    m_radius = radius;
}
