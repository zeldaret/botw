#pragma once

#include <Havok/Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

class hkpConvexTranslateShape : public hkpConvexTransformShapeBase {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpConvexTranslateShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::CONVEX_TRANSLATE)

    HK_FORCE_INLINE hkpConvexTranslateShape() {}
    HK_FORCE_INLINE hkpConvexTranslateShape(
        const hkpConvexShape* childShape, const hkVector4& translation,
        hkpShapeContainer::ReferencePolicy ref = hkpShapeContainer::REFERENCE_POLICY_INCREMENT);

    void getSupportingVertex(hkVector4Parameter direction,
                             hkcdVertex& supportingVertexOut) const override;
    void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds,
                                    hkcdVertex* verticesOut) const override;
    void getCentre(hkVector4& centreOut) const override;
    HK_FORCE_INLINE int getNumCollisionSpheres() const override;
    const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const override;
    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;
    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override;
    void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                              hkpRayHitCollector& collector) const override;
    void getFirstVertex(hkVector4& v) const override;
    hkReal getMaximumProjection(const hkVector4& direction) const override;
    const hkpShapeContainer* getContainer() const override;
    int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const override;

    inline const hkpConvexShape* getChildShape() const;
    inline hkVector4& getTranslation();
    inline const hkVector4& getTranslation() const;

    hkpConvexTranslateShape(class hkFinishLoadedObjectFlag flag);

protected:
    hkVector4 m_translation;
};

HK_FORCE_INLINE
hkpConvexTranslateShape::hkpConvexTranslateShape(const hkpConvexShape* childShape,
                                                 const hkVector4& translation,
                                                 hkpShapeContainer::ReferencePolicy ref)
    : hkpConvexTransformShapeBase(HKCD_SHAPE_TYPE_FROM_CLASS(hkpConvexTranslateShape),
                                  childShape->getRadius(), childShape, ref) {
    hkVector4 t = translation;
    t.setW(0);
    m_translation = t;
    m_childShapeSizeForSpu = 0;
}

inline const hkpConvexShape* hkpConvexTranslateShape::getChildShape() const {
    return static_cast<const hkpConvexShape*>(m_childShape.getChild());
}

inline const hkVector4& hkpConvexTranslateShape::getTranslation() const {
    return m_translation;
}

inline hkVector4& hkpConvexTranslateShape::getTranslation() {
    return m_translation;
}

HK_FORCE_INLINE int hkpConvexTranslateShape::getNumCollisionSpheres() const {
    return getChildShape()->getNumCollisionSpheres();
}