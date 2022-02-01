#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Geometry/Collide/Shapes/hkcdShape.h>

using hkpVertexId = hkUint16;
using hkpShapeKey = hkUint32;

class hkAabb;
class hkSphere;
class hkcdVertex;
class hkpCdBody;
class hkpRayHitCollector;
struct hkpShapeRayBundleCastInput;
struct hkpShapeRayBundleCastOutput;
struct hkpShapeRayCastInput;
struct hkpShapeRayCastOutput;

/// Base interface for all physics shapes.
class hkpShapeBase : public hkcdShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpShapeBase)
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::INVALID)

    HK_FORCE_INLINE hkpShapeBase() = default;
    HK_FORCE_INLINE explicit hkpShapeBase(ShapeType type) : hkcdShape(type) {}
    explicit hkpShapeBase(hkFinishLoadedObjectFlag flag);

    /// Returns true if the shape is a hkpConvexShape.
    virtual bool isConvex() const { return false; }

    /// Returns true if the shape is a hkpBvTreeShape.
    HK_FORCE_INLINE bool isBvTree() const;

    /// Returns true if the shape is a hkpShapeCollection.
    HK_FORCE_INLINE bool isCollection() const;

    virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& aabbOut) const;

    virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& output) const;

    virtual void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                                      hkpRayHitCollector& collector) const;

    virtual hkVector4Comparison castRayBundle(const hkpShapeRayBundleCastInput& input,
                                              hkpShapeRayBundleCastOutput& output,
                                              hkVector4ComparisonParameter mask) const;

    virtual void getSupportingVertex(hkVector4Parameter direction,
                                     hkcdVertex& supportingVertexOut) const;

    virtual void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds,
                                            hkcdVertex* vertexArrayOut) const;

    virtual void getCentre(hkVector4& centreOut) const;

    virtual int getNumCollisionSpheres() const;

    virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;

    virtual int weldContactPoint(hkpVertexId* featurePoints, hkUint8& numFeaturePoints,
                                 hkVector4& contactPointWs, const hkTransform* thisObjTransform,
                                 const class hkpConvexShape* collidingConvexShape,
                                 const hkTransform* collidingTransform,
                                 hkVector4& separatingNormalInOut) const;
};

inline bool hkpShapeBase::isBvTree() const {
    switch (m_type) {
    case hkcdShapeType::BV_TREE:
    case hkcdShapeType::MOPP:
    case hkcdShapeType::STATIC_COMPOUND:
    case hkcdShapeType::BV_COMPRESSED_MESH:
    case hkcdShapeType::TRI_SAMPLED_HEIGHT_FIELD_BV_TREE:
        return true;
    default:
        return false;
    }
}

inline bool hkpShapeBase::isCollection() const {
    switch (m_type) {
    case hkcdShapeType::COLLECTION:
    case hkcdShapeType::LIST:
    case hkcdShapeType::EXTENDED_MESH:
    case hkcdShapeType::TRI_SAMPLED_HEIGHT_FIELD_COLLECTION:
        return true;
    default:
        return false;
    }
}
