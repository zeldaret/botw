#pragma once

#include <Havok/Common/Base/Math/Vector/hkFourTransposedPoints.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

struct hkStridedVertices;
class hkpConvexVerticesConnectivity;

class hkpConvexVerticesShape : public hkpConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpConvexVerticesShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::CONVEX_VERTICES)

    struct BuildConfig {
        BuildConfig();

        hkBool m_createConnectivity;
        hkBool m_shrinkByConvexRadius;
        hkBool m_useOptimizedShrinking;
        hkReal m_convexRadius;
        int m_maxVertices;
        hkReal m_maxRelativeShrink;
        hkReal m_maxShrinkingVerticesDisplacement;
        hkReal m_maxCosAngleForBevelPlanes;
    };

    explicit hkpConvexVerticesShape(const hkStridedVertices& vertices,
                                    const BuildConfig& config = BuildConfig());

    hkpConvexVerticesShape(const hkStridedVertices& vertsIn,
                           const hkArray<hkVector4>& planeEquations,
                           hkReal radius = hkConvexShapeDefaultRadius);

    hkpConvexVerticesShape(hkFourTransposedPoints* rotatedVertices, int numVertices,
                           hkVector4* planes, int numPlanes, const hkAabb& aabb,
                           hkReal radius = hkConvexShapeDefaultRadius);

    explicit hkpConvexVerticesShape(hkReal radius = hkConvexShapeDefaultRadius);

    explicit hkpConvexVerticesShape(hkFinishLoadedObjectFlag flag);

    ~hkpConvexVerticesShape() override;

    void getOriginalVertices(hkArray<hkVector4>& vertices) const;
    const hkArray<hkVector4>& getPlaneEquations() const;
    void setPlaneEquations(const hkArray<hkVector4>& planes);
    void setRadiusUnchecked(hkReal radius) { m_radius = radius; }
    void transformVerticesAndPlaneEquations(const hkTransform& t);
    void copyVertexData(const hkReal* vertexIn, int byteStriding, int numVertices);

    const hkpConvexVerticesConnectivity* getConnectivity() const { return m_connectivity; }
    void setConnectivity(const hkpConvexVerticesConnectivity* connect, bool sort = true);

    void getFirstVertex(hkVector4& v) const override;
    void getSupportingVertex(hkVector4Parameter direction,
                             hkcdVertex& supportingVertexOut) const override;
    void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds,
                                    hkcdVertex* verticesOut) const override;

    void getCentre(hkVector4& centreOut) const override;
    int getNumCollisionSpheres() const override { return m_numVertices; }
    const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const override;
    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;
    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override;

    hkVector4 m_aabbHalfExtents;
    hkVector4 m_aabbCenter;

    hkArray<hkFourTransposedPoints> m_rotatedVertices;
    hkInt32 m_numVertices;

    hkBool m_useSpuBuffer;
    mutable hkArray<hkVector4> m_planeEquations;
    mutable const hkpConvexVerticesConnectivity* m_connectivity;

protected:
    void sortPlanes();
};
