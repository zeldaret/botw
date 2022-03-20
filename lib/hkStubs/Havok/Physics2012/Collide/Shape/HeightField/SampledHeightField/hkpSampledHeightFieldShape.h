#pragma once

#include <Havok/Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldBaseCinfo.h>
#include <Havok/Physics2012/Collide/Shape/HeightField/hkpHeightFieldShape.h>

class hkpSampledHeightFieldShape : public hkpHeightFieldShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpHeightFieldShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::SAMPLED_HEIGHT_FIELD)

    enum HeightFieldType {
        /// hkpStorageSampledHeightFieldShape, stores values as hkReals
        HEIGHTFIELD_STORAGE = 0,
        /// hkpCompressedSampledHeightFieldShape, stores values as hkUint16s
        HEIGHTFIELD_COMPRESSED,
        HEIGHTFIELD_USER,
        HEIGHTFIELD_MAX_ID
    };

    explicit hkpSampledHeightFieldShape(const hkpSampledHeightFieldBaseCinfo& ci,
                                        HeightFieldType type = HEIGHTFIELD_USER);

    hkpSampledHeightFieldShape()
        : hkpHeightFieldShape(HKCD_SHAPE_TYPE_FROM_CLASS(hkpSampledHeightFieldShape)) {}

    explicit hkpSampledHeightFieldShape(hkFinishLoadedObjectFlag flag);

    ~hkpSampledHeightFieldShape() override;

    void getCinfo(hkpSampledHeightFieldBaseCinfo& cinfo) const;

    HK_FORCE_INLINE hkReal getHeightAt(int x, int z) const;

    HK_FORCE_INLINE hkBool getTriangleFlip() const;

    void buildCoarseMinMaxTree(int coarseness = 3);

    virtual void getCoarseMinMax(int level, int x, int z, hkVector4& minOut,
                                 hkVector4& maxOut) const;

    void setMinMaxTreeCoarseness(int coarseness);

    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;

    void collideSpheres(const CollideSpheresInput& input,
                        SphereCollisionOutput* outputArray) const override;

    void castSphere(const hkpSphereCastInput& input, const hkpCdBody& cdBody,
                    hkpRayHitCollector& collector) const override;

    hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& output) const override;

    void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                              hkpRayHitCollector& collector) const override;

    virtual hkReal getHeightAtImpl(int x, int z) const;
    virtual hkBool getTriangleFlipImpl() const;

    using RayCastInternalFunc = void (hkpSampledHeightFieldShape::*)(const hkpShapeRayCastInput&,
                                                                     const hkpCdBody&,
                                                                     hkpRayHitCollector&) const;
    static RayCastInternalFunc s_rayCastFunc;

    void castRayDefault(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                        hkpRayHitCollector& collector) const;
    void castRayDda(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                    hkpRayHitCollector& collector) const;
    void castRayCoarseTree(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                           hkpRayHitCollector& collector) const;

    using SphereCastInternalFunc = void (hkpSampledHeightFieldShape::*)(const hkpSphereCastInput&,
                                                                        const hkpCdBody&,
                                                                        hkpRayHitCollector&) const;
    static SphereCastInternalFunc s_sphereCastFunc;

    void castSphereDefault(const hkpSphereCastInput& input, const hkpCdBody& cdBody,
                           hkpRayHitCollector& collector) const;
    void castSphereDda(const hkpSphereCastInput& input, const hkpCdBody& cdBody,
                       hkpRayHitCollector& collector) const;
    void castSphereCoarseTree(const hkpSphereCastInput& input, const hkpCdBody& cdBody,
                              hkpRayHitCollector& collector) const;

protected:
    void castRayDdaInternal(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                            hkBool reportPenetratingStartPosition, hkReal maxExtraPenetration,
                            hkpRayHitCollector& collector) const;

    void castRayCoarseTreeInternal(const hkVector4& from, const hkVector4& to,
                                   const hkpCdBody& cdBody, hkpRayHitCollector& collector) const;

    HK_FORCE_INLINE void _getHeightAndNormalAt(int xPos, int zPos, hkReal subX, hkReal subZ,
                                               hkVector4& normalOut, hkReal& heightOut,
                                               int& triangleIndexOut) const;

    HK_FORCE_INLINE void calcMinMax(int coarseness, int x, int z, hkReal& minheightOut,
                                    hkReal& maxheightOut) const;

    struct AABBStackElement {
        hkAabb aabb;
        int level;
        int x;
        int z;
    };

    HK_FORCE_INLINE void findStartCell(AABBStackElement& startOut, const hkVector4& from,
                                       const hkVector4& to) const;

    HK_FORCE_INLINE void rayTriangleQuadCheck(const struct hkcdRay& ray, hkAabb& aabb, int x, int z,
                                              const hkVector4Comparison& flipSelect,
                                              const hkpCdBody& cdBody,
                                              hkpRayHitCollector& collector) const;

public:
    struct CoarseMinMaxLevel {
        HK_DECLARE_CLASS_ALLOCATOR(CoarseMinMaxLevel)
        HK_DECLARE_REFLECTION()

        CoarseMinMaxLevel() {}
        explicit CoarseMinMaxLevel(hkFinishLoadedObjectFlag f) : m_minMaxData(f) {}
        CoarseMinMaxLevel(const CoarseMinMaxLevel& l) : m_xRes(l.m_xRes), m_zRes(l.m_zRes) {
            m_minMaxData = l.m_minMaxData;
        }

        hkArray<hkVector4> m_minMaxData;
        int m_xRes;
        int m_zRes;
    };
    hkArray<CoarseMinMaxLevel> m_coarseTreeData;

    void getHeightAndNormalAt(int xPos, int zPos, hkReal subX, hkReal subZ, hkVector4& normalOut,
                              hkReal& heightOut, int& triangleIndexOut) const;

    int m_coarseness;
    hkReal m_raycastMinY;
    hkReal m_raycastMaxY;

    int m_xRes;
    int m_zRes;

    hkReal m_heightCenter;

    hkBool m_useProjectionBasedHeight;

    hkEnum<HeightFieldType, hkUint8> m_heightfieldType;

    hkVector4 m_intToFloatScale;
    hkVector4 m_floatToIntScale;
    hkVector4 m_floatToIntOffsetFloorCorrected;
    hkVector4 m_extents;
};
