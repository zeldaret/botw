#pragma once

#include <Havok/Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

class hkpConvexTransformShape : public hkpConvexTransformShapeBase {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpConvexTransformShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::CONVEX_TRANSFORM)

    HK_FORCE_INLINE hkpConvexTransformShape() {}

    hkpConvexTransformShape(
        const hkpConvexShape* childShape, const hkTransform& transform,
        hkpShapeContainer::ReferencePolicy ref = hkpShapeContainer::REFERENCE_POLICY_INCREMENT);

    hkpConvexTransformShape(
        const hkpConvexShape* childShape, const hkQsTransform& transform,
        hkpShapeContainer::ReferencePolicy ref = hkpShapeContainer::REFERENCE_POLICY_INCREMENT);

    explicit hkpConvexTransformShape(hkFinishLoadedObjectFlag flag);

    void setTransform(const hkQsTransform& transform);
    inline void setTransform(const hkTransform& transform);
    inline void getTransform(hkTransform* HK_RESTRICT transform) const;
    inline const hkQsTransform& getQsTransform() const;

    inline const hkVector4& getExtraScale() const;

    inline const hkpConvexShape* getChildShape() const;

    inline void transformVertex(hkVector4Parameter localVertex,
                                hkVector4* HK_RESTRICT vertexOut) const;

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

    void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                              hkpRayHitCollector& collector) const override;

    const hkpShapeContainer* getContainer() const override;

    int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const override;

    void getFirstVertex(hkVector4& v) const override;

protected:
    hkQsTransform m_transform;
    hkVector4 m_extraScale;
};

inline void hkpConvexTransformShape::setTransform(const hkTransform& transform) {
    m_transform.setFromTransformNoScale(transform);
    m_extraScale.setZero();
}

inline void hkpConvexTransformShape::getTransform(hkTransform* transform) const {
    m_transform.copyToTransformNoScale(*transform);
}

inline const hkQsTransform& hkpConvexTransformShape::getQsTransform() const {
    return m_transform;
}

inline const hkVector4& hkpConvexTransformShape::getExtraScale() const {
    return m_extraScale;
}

inline const hkpConvexShape* hkpConvexTransformShape::getChildShape() const {
    return static_cast<const hkpConvexShape*>(m_childShape.getChild());
}

inline void hkpConvexTransformShape::transformVertex(const hkVector4f& localVertex,
                                                     hkVector4* vertexOut) const {
    hkVector4 center;
    center.set(m_transform.m_translation.getW(), m_transform.m_scale.getW(), m_extraScale.getW(),
               hkSimdReal::getConstant<HK_QUADREAL_0>());

    hkVector4 relVertex;
    relVertex.setSub(localVertex, center);
    vertexOut->setMul(localVertex, m_transform.getScale());
    vertexOut->addMul(m_extraScale, relVertex);

    vertexOut->_setRotatedDir(m_transform.getRotation(), *vertexOut);
    vertexOut->add(m_transform.getTranslation());
}

inline int hkpConvexTransformShape::getNumCollisionSpheres() const {
    return getChildShape()->getNumCollisionSpheres();
}
