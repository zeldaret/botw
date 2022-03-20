#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeContainer.h>
#include <Havok/Physics2012/Collide/Util/Welding/hkpWeldingUtility.h>

struct hkGeometry;
class hkpBvCompressedMeshShapeCinfo;

class hkpBvCompressedMeshShape : public hkpBvTreeShape, public hkpShapeContainer {
public:
    enum PerPrimitiveDataMode {
        PER_PRIMITIVE_DATA_NONE,
        PER_PRIMITIVE_DATA_8_BIT,
        PER_PRIMITIVE_DATA_PALETTE,
        PER_PRIMITIVE_DATA_STRING_PALETTE,
    };

    enum PrimitiveType {
        PRIMITIVE_TYPE_BOX,
        PRIMITIVE_TYPE_HULL,
        PRIMITIVE_TYPE_SPHERE,
        PRIMITIVE_TYPE_CAPSULE,
        PRIMITIVE_TYPE_CYLINDER,
    };

    enum Config {
#if HK_POINTER_SIZE == 8
#ifdef HK_REAL_IS_DOUBLE
        NUM_BYTES_FOR_TREE = 224,
#else
        NUM_BYTES_FOR_TREE = 160,
#endif
#else
#ifdef HK_REAL_IS_DOUBLE
        NUM_BYTES_FOR_TREE = 224,
#else
        NUM_BYTES_FOR_TREE = 144,
#endif
#endif

        MAX_NUM_VERTICES_PER_HULL = 255,

        MAX_NUM_PRIMITIVES = 1 << 23
    };

public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpBvCompressedMeshShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::BV_COMPRESSED_MESH)

    explicit hkpBvCompressedMeshShape(const hkpBvCompressedMeshShapeCinfo& cInfo);
    explicit hkpBvCompressedMeshShape(hkFinishLoadedObjectFlag flag);
    HK_FORCE_INLINE hkpBvCompressedMeshShape() {}

    ~hkpBvCompressedMeshShape() override;

    HK_FORCE_INLINE hkReal getConvexRadius() const;

    hkUint32 getPrimitiveUserData(hkpShapeKey key) const;
    hkStringPtr getPrimitiveUserString(hkpShapeKey key) const;

    HK_FORCE_INLINE PerPrimitiveDataMode getCollisionFilterInfoMode() const;
    HK_FORCE_INLINE PerPrimitiveDataMode getUserDataMode() const;
    HK_FORCE_INLINE hkArray<hkUint32>& accessCollisionFilterInfoPalette();
    HK_FORCE_INLINE hkArray<hkUint32>& accessUserDataPalette();
    HK_FORCE_INLINE hkArray<hkStringPtr>& accessUserStringPalette();

    void convertToGeometry(hkGeometry& geometryOut, const hkArray<hkpShapeKey>* inclKeys = nullptr,
                           const hkArray<hkpShapeKey>* exclKeys = nullptr) const;

    const hkpShapeContainer* getContainer() const override { return this; }

    int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const override;

    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;

    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override;

    void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& body,
                              hkpRayHitCollector& collector) const override;

    void queryAabb(const hkAabb& aabb, hkArray<hkpShapeKey>& hits) const override;

    hkUint32 queryAabbImpl(const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys) const override;

    void castAabbImpl(const hkAabb& from, hkVector4Parameter to,
                      hkpAabbCastCollector& collector) const override;

    int getNumChildShapes() const override;

    hkpShapeKey getFirstKey() const override;

    hkpShapeKey getNextKey(hkpShapeKey oldKey) const override;

    const hkpShape* getChildShape(hkpShapeKey key, hkpShapeBuffer& buffer) const override;

    hkUint32 getCollisionFilterInfo(hkpShapeKey key) const override;

protected:
    hkReal m_convexRadius;
    hkEnum<hkpWeldingUtility::WeldingType, hkUint8> m_weldingType;
    hkBool m_hasPerPrimitiveCollisionFilterInfo;
    hkBool m_hasPerPrimitiveUserData;
    hkArray<hkUint32> m_collisionFilterInfoPalette;
    hkArray<hkUint32> m_userDataPalette;
    hkArray<hkStringPtr> m_userStringPalette;
    alignas(16) hkUint8 m_tree[NUM_BYTES_FOR_TREE];

    friend struct hkpBvCompressedMeshShape_Internals;

public:
    alignas(16) static hkVector4 g_vertexBufferPool[HK_MAX_NUM_THREADS][MAX_NUM_VERTICES_PER_HULL];
};

inline hkReal hkpBvCompressedMeshShape::getConvexRadius() const {
    return m_convexRadius;
}

inline hkpBvCompressedMeshShape::PerPrimitiveDataMode
hkpBvCompressedMeshShape::getCollisionFilterInfoMode() const {
    return m_hasPerPrimitiveCollisionFilterInfo ?
               (m_collisionFilterInfoPalette.getSize() ? PER_PRIMITIVE_DATA_PALETTE :
                                                         PER_PRIMITIVE_DATA_8_BIT) :
               PER_PRIMITIVE_DATA_NONE;
}

inline hkpBvCompressedMeshShape::PerPrimitiveDataMode
hkpBvCompressedMeshShape::getUserDataMode() const {
    if (!m_hasPerPrimitiveUserData)
        return PER_PRIMITIVE_DATA_NONE;

    if (m_userDataPalette.getSize() > 0)
        return PER_PRIMITIVE_DATA_PALETTE;

    if (m_userStringPalette.getSize() > 0)
        return PER_PRIMITIVE_DATA_STRING_PALETTE;

    return PER_PRIMITIVE_DATA_8_BIT;
}

inline hkArray<hkUint32>& hkpBvCompressedMeshShape::accessCollisionFilterInfoPalette() {
    return m_collisionFilterInfoPalette;
}

inline hkArray<hkUint32>& hkpBvCompressedMeshShape::accessUserDataPalette() {
    return m_userDataPalette;
}

inline hkArray<hkStringPtr>& hkpBvCompressedMeshShape::accessUserStringPalette() {
    return m_userStringPalette;
}
