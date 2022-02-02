#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

class hkpCylinderShape : public hkpConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCylinderShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::CYLINDER)

    enum VertexIdEncoding {
        VERTEX_ID_ENCODING_IS_BASE_A_SHIFT = 7,
        VERTEX_ID_ENCODING_SIN_SIGN_SHIFT = 6,
        VERTEX_ID_ENCODING_COS_SIGN_SHIFT = 5,
        VERTEX_ID_ENCODING_IS_SIN_LESSER_SHIFT = 4,
        VERTEX_ID_ENCODING_VALUE_MASK = 0x0f
    };

    HK_FORCE_INLINE hkpCylinderShape() {}

    hkpCylinderShape(const hkVector4& vertexA, const hkVector4& vertexB, hkReal cylinderRadius,
                     hkReal paddingRadius = hkConvexShapeDefaultRadius);

    explicit hkpCylinderShape(hkFinishLoadedObjectFlag flag);

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

    inline const hkVector4* getVertices() const;

    HK_FORCE_INLINE const hkVector4& getVertex(int i) const;
    template <int I>
    HK_FORCE_INLINE const hkVector4& getVertex() const;

    HK_FORCE_INLINE void setVertex(int i, const hkVector4& position);
    template <int I>
    HK_FORCE_INLINE void setVertex(hkVector4Parameter position);

    hkReal getCylinderRadius() const;
    void setCylinderRadius(hkReal radius);

    hkReal getCylinderBaseRadiusFactorForHeightfieldCollisions() {
        return m_cylBaseRadiusFactorForHeightFieldCollisions;
    }

    inline void setCylinderBaseRadiusFactorForHeightfieldCollisions(hkReal radiusFactor) {
        m_cylBaseRadiusFactorForHeightFieldCollisions = radiusFactor;
    }

    void presetPerpendicularVector();

    static void setNumberOfVirtualSideSegments(int numSegments);

    void getFirstVertex(hkVector4& v) const override;

    HK_FORCE_INLINE static void initRoundUpThreshold();

protected:
    hkReal m_cylRadius;
    hkReal m_cylBaseRadiusFactorForHeightFieldCollisions;
    hkVector4 m_vertexA;
    hkVector4 m_vertexB;
    hkVector4 m_perpendicular1;
    hkVector4 m_perpendicular2;

private:
    void decodeVertexId(hkpVertexId code, hkVector4& result) const;

    static hkReal s_virtualTesselationParameter;
    static hkReal s_virtualTesselationParameterInv;
    static hkReal s_intRoundUpThreshold;
};

inline int hkpCylinderShape::getNumCollisionSpheres() const {
    return 16 + 2;
}

inline const hkVector4* hkpCylinderShape::getVertices() const {
    return &m_vertexA;
}

inline const hkVector4& hkpCylinderShape::getVertex(int i) const {
    return getVertices()[i];
}

template <int I>
inline const hkVector4& hkpCylinderShape::getVertex() const {
    static_assert(I == 0 || I == 1, "invalid index");
    return getVertices()[I];
}

inline void hkpCylinderShape::setVertex(int i, const hkVector4& position) {
    (&m_vertexA)[i] = position;
}

template <int I>
inline void hkpCylinderShape::setVertex(const hkVector4f& position) {
    static_assert(I == 0 || I == 1, "invalid index");
    (&m_vertexA)[I] = position;
}

inline void hkpCylinderShape::initRoundUpThreshold() {
    if (s_intRoundUpThreshold < 0.0f) {
        for (hkReal value = 0.0f; value < 1.1f; value += 0.01f) {
            if (hkMath::hkToIntFast(value) != 0) {
                s_intRoundUpThreshold = 1.0f - value;
                return;
            }
        }
        s_intRoundUpThreshold = 0.0f;
    }
}
