#pragma once

#include <Havok/Physics2012/Collide/Shape/Convex/hkpConvexShape.h>
#include <Havok/Physics2012/Collide/Util/Welding/hkpWeldingUtility.h>

class hkpTriangleShape : public hkpConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpTriangleShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::TRIANGLE)

public:
    explicit hkpTriangleShape(hkFinishLoadedObjectFlag flag);

    HK_FORCE_INLINE explicit hkpTriangleShape(
        hkReal radius = hkConvexShapeDefaultRadius, hkUint16 weldingInfo = 0,
        hkpWeldingUtility::WeldingType type = hkpWeldingUtility::WELDING_TYPE_NONE);

    HK_FORCE_INLINE hkpTriangleShape(const hkVector4& v0, const hkVector4& v1, const hkVector4& v2,
                                     hkReal radius = hkConvexShapeDefaultRadius);

    HK_FORCE_INLINE const hkVector4* getVertices() const;
    HK_FORCE_INLINE hkVector4& getVertex(int i);
    HK_FORCE_INLINE const hkVector4& getVertex(int i) const;
    template <int I>
    HK_FORCE_INLINE const hkVector4& getVertex() const;

    HK_FORCE_INLINE void setVertex(int i, const hkVector4& vertex);
    template <int I>
    HK_FORCE_INLINE void setVertex(hkVector4Parameter vertex);

    HK_FORCE_INLINE hkUint16 getWeldingInfo() const;
    HK_FORCE_INLINE void setWeldingInfo(hkUint16 info);
    HK_FORCE_INLINE hkpWeldingUtility::WeldingType getWeldingType() const;
    HK_FORCE_INLINE void setWeldingType(hkpWeldingUtility::WeldingType type);

    HK_FORCE_INLINE bool isExtruded() const;
    HK_FORCE_INLINE const hkVector4& getExtrusion() const;
    HK_FORCE_INLINE void setExtrusion(const hkVector4& extrusion);

    void getSupportingVertex(hkVector4Parameter direction,
                             hkcdVertex& supportingVertexOut) const override;

    void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds,
                                    hkcdVertex* verticesOut) const override;

    int weldContactPoint(hkpVertexId* featurePoints, hkUint8& numFeaturePoints,
                         hkVector4& contactPointWs, const hkTransform* thisObjTransform,
                         const hkpConvexShape* collidingShape,
                         const hkTransform* collidingTransform,
                         hkVector4& separatingNormalInOut) const override;

    void getCentre(hkVector4& centreOut) const override;

    HK_FORCE_INLINE int getNumCollisionSpheres() const override;

    const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const override;

    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;

    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override;

    hkVector4Comparison castRayBundle(const hkpShapeRayBundleCastInput& input,
                                      hkpShapeRayBundleCastOutput& results,
                                      hkVector4ComparisonParameter mask) const override;

    void getFirstVertex(hkVector4& v) const override;

protected:
    hkUint16 m_weldingInfo;
    hkEnum<hkpWeldingUtility::WeldingType, hkUint8> m_weldingType;
    hkUint8 m_isExtruded;

    hkVector4 m_vertexA;
    hkVector4 m_vertexB;
    hkVector4 m_vertexC;

    hkVector4 m_extrusion;
};

inline hkpTriangleShape::hkpTriangleShape(hkReal radius, hkUint16 weldingInfo,
                                          hkpWeldingUtility::WeldingType type)
    : hkpConvexShape(HKCD_SHAPE_TYPE_FROM_CLASS(hkpTriangleShape), radius) {
    setWeldingInfo(weldingInfo);
    setWeldingType(type);
    m_extrusion.setZero();
    m_isExtruded = 0;
}

inline hkpTriangleShape::hkpTriangleShape(const hkVector4& v0, const hkVector4& v1,
                                          const hkVector4& v2, hkReal radius)
    : hkpConvexShape(HKCD_SHAPE_TYPE_FROM_CLASS(hkpTriangleShape), radius) {
    m_vertexA = v0;
    m_vertexB = v1;
    m_vertexC = v2;

    setWeldingInfo(0);
    setWeldingType(hkpWeldingUtility::WELDING_TYPE_NONE);
    m_extrusion.setZero();
    m_isExtruded = 0;
}

inline const hkVector4* hkpTriangleShape::getVertices() const {
    return &m_vertexA;
}

inline hkVector4& hkpTriangleShape::getVertex(int i) {
    return (&m_vertexA)[i];
}

inline const hkVector4& hkpTriangleShape::getVertex(int i) const {
    return (&m_vertexA)[i];
}

template <int I>
inline const hkVector4& hkpTriangleShape::getVertex() const {
    return (&m_vertexA)[I];
}

inline void hkpTriangleShape::setVertex(int i, const hkVector4& vertex) {
    getVertex(i) = vertex;
}

template <int I>
inline void hkpTriangleShape::setVertex(const hkVector4f& vertex) {
    (&m_vertexA)[I] = vertex;
}

inline hkUint16 hkpTriangleShape::getWeldingInfo() const {
    return m_weldingInfo;
}

inline void hkpTriangleShape::setWeldingInfo(hkUint16 info) {
    m_weldingInfo = info;
}

inline hkpWeldingUtility::WeldingType hkpTriangleShape::getWeldingType() const {
    return m_weldingType;
}

inline void hkpTriangleShape::setWeldingType(hkpWeldingUtility::WeldingType type) {
    m_weldingType = type;
}

inline bool hkpTriangleShape::isExtruded() const {
    return m_isExtruded;
}

inline const hkVector4& hkpTriangleShape::getExtrusion() const {
    return m_extrusion;
}

inline void hkpTriangleShape::setExtrusion(const hkVector4& extrusion) {
    m_extrusion = extrusion;
}

inline int hkpTriangleShape::getNumCollisionSpheres() const {
    return 3 + 3 * m_isExtruded;
}
