#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeContainer.h>
#include <Havok/Physics2012/Internal/Collide/StaticCompound/hkpShapeKeyTable.h>

class hkpStaticCompoundShape : public hkpBvTreeShape, public hkpShapeContainer {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpStaticCompoundShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::STATIC_COMPOUND)

    struct Instance {
    public:
        enum {
            FLAG_IS_LEAF = 1 << 0,
            FLAG_HAS_TRANSFORM = 1 << 1,
            FLAG_HAS_SCALE = 1 << 2,
            FLAG_HAS_FLIP = 1 << 3,

            FLAG_IS_DISABLED = 1 << 4,
            FLAG_HAS_DISABLED_SMALL_KEYS = 1 << 5,
            FLAG_HAS_DISABLED_LARGE_KEYS = 1 << 6,

            FLAGS_HAS_DISABLED_KEYS = FLAG_HAS_DISABLED_SMALL_KEYS | FLAG_HAS_DISABLED_LARGE_KEYS,
            FLAGS_ALL = (1 << 7) - 1,
        };

        enum : hkUint32 {
            NUM_BITS_FOR_FLAGS = 7,
            NUM_BITS_FOR_SHAPE_SIZE = 4,
            NUM_BITS_FOR_DISABLED_SMALL_KEYS = 37
        };

    protected:
        HK_FORCE_INLINE void setShapeSizeForSpu(hkUint32 size);
        HK_FORCE_INLINE void setFlags(hkUint32 flags);

        hkQsTransform m_transform;
        const hkpShape* m_shape;

    public:
        HK_DECLARE_CLASS_ALLOCATOR(Instance)
        HK_DECLARE_REFLECTION()

        HK_FORCE_INLINE const hkQsTransform& getTransform() const;
        HK_FORCE_INLINE const hkpShape* getShape() const;
        HK_FORCE_INLINE hkUint32 getShapeSizeForSpu() const;
        HK_FORCE_INLINE hkUint32 getFlags() const;

        hkUint32 m_filterInfo;
        hkUint32 m_childFilterInfoMask;
        hkUlong m_userData;

        friend class hkpStaticCompoundShape;
        friend class hkpStaticCompoundShape_Internals;
    };

    enum Config {
#ifdef HK_REAL_IS_DOUBLE
        NUM_BYTES_FOR_TREE = 96
#else
        NUM_BYTES_FOR_TREE = 48
#endif
    };

public:
    explicit hkpStaticCompoundShape(ReferencePolicy ref = REFERENCE_POLICY_INCREMENT);
    explicit hkpStaticCompoundShape(hkFinishLoadedObjectFlag flag);

    ~hkpStaticCompoundShape() override;

    int addInstance(const hkpShape* shape, const hkQsTransform& transform);

    void bake();

    HK_FORCE_INLINE void decomposeShapeKey(hkpShapeKey keyIn, int& instanceIdOut,
                                           hkpShapeKey& childKeyOut) const;

    HK_FORCE_INLINE hkpShapeKey composeShapeKey(int instanceId, hkpShapeKey childKey) const;

    HK_FORCE_INLINE hkInt8 getNumBitsForChildShapeKey() const;

    HK_FORCE_INLINE const hkArray<Instance>& getInstances() const;

    HK_FORCE_INLINE void setInstanceFilterInfo(int instanceId, hkUint32 filterInfo);
    HK_FORCE_INLINE hkUint32 getInstanceFilterInfo(int instanceId) const;

    HK_FORCE_INLINE void setInstanceFilterInfoMask(int instanceId, hkUint32 filterInfoMask);
    HK_FORCE_INLINE hkUint32 getInstanceFilterInfoMask(int instanceId) const;

    HK_FORCE_INLINE void setInstanceUserData(int instanceId, hkUlong userData);
    HK_FORCE_INLINE hkUlong getInstanceUserData(int instanceId) const;

    HK_FORCE_INLINE void setInstanceExtraInfo(int instanceId, hkUint16 instanceInfo);
    HK_FORCE_INLINE hkUint16 getInstanceExtraInfo(int instanceId) const;
    HK_FORCE_INLINE const hkArray<hkUint16>& getInstanceExtraInfos() const;

    HK_FORCE_INLINE void setInstanceEnabled(int instanceId, hkBool32 isEnabled);
    HK_FORCE_INLINE hkBool32 isInstanceEnabled(int instanceId) const;

    void setShapeKeyEnabled(hkpShapeKey key, hkBool32 isEnabled);
    hkBool32 isShapeKeyEnabled(hkpShapeKey key) const;

    void enableAllInstancesAndShapeKeys();

    void castAabb(const hkpShape* shape, const hkTransform& transform, hkVector4Parameter to,
                  hkpAabbCastCollector& collector, hkReal tolerance = 0.0f) const;

    const hkpShapeContainer* getContainer() const override { return this; }
    int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const override;
    hkReal getMaximumProjection(const hkVector4& direction) const override;
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
    hkInt8 m_numBitsForChildShapeKey;
    hkInt8 m_referencePolicy;
    hkUint32 m_childShapeKeyMask;

    hkArray<Instance> m_instances;
    hkArray<hkUint16> m_instanceExtraInfos;
    hkpShapeKeyTable m_disabledLargeShapeKeyTable;

    alignas(16) hkUint8 m_tree[NUM_BYTES_FOR_TREE];

    friend class hkpStaticCompoundShape_Internals;
};

inline const hkQsTransform& hkpStaticCompoundShape::Instance::getTransform() const {
    return m_transform;
}

inline const hkpShape* hkpStaticCompoundShape::Instance::getShape() const {
    return m_shape;
}

inline void hkpStaticCompoundShape::Instance::setFlags(hkUint32 flags) {
    m_transform.m_translation.setInt24W(
        int((m_transform.m_translation.getInt24W() & ~FLAGS_ALL) | flags));
}

inline hkUint32 hkpStaticCompoundShape::Instance::getFlags() const {
    return m_transform.m_translation.getInt24W() & FLAGS_ALL;
}

inline void hkpStaticCompoundShape::Instance::setShapeSizeForSpu(hkUint32 size) {
    const hkUint32 shapeSizeMask = ((1 << NUM_BITS_FOR_SHAPE_SIZE) - 1) << NUM_BITS_FOR_FLAGS;
    hkUint32 bitfield = (m_transform.m_translation.getInt24W() & ~shapeSizeMask);

    const hkUint32 storedShapeSize = size / 16;

    bitfield |= storedShapeSize << NUM_BITS_FOR_FLAGS;
    m_transform.m_translation.setInt24W(int(bitfield));
}

inline hkUint32 hkpStaticCompoundShape::Instance::getShapeSizeForSpu() const {
    return ((m_transform.m_translation.getInt24W() >> NUM_BITS_FOR_FLAGS) &
            ((1 << NUM_BITS_FOR_SHAPE_SIZE) - 1)) *
           16;
}

inline void hkpStaticCompoundShape::decomposeShapeKey(hkpShapeKey keyIn, int& instanceIdOut,
                                                      hkpShapeKey& childKeyOut) const {
    instanceIdOut = int(keyIn >> m_numBitsForChildShapeKey);
    childKeyOut = keyIn & m_childShapeKeyMask;
}

inline hkpShapeKey hkpStaticCompoundShape::composeShapeKey(int instanceId,
                                                           hkpShapeKey childKey) const {
    return (instanceId << m_numBitsForChildShapeKey) | childKey;
}

inline hkInt8 hkpStaticCompoundShape::getNumBitsForChildShapeKey() const {
    return m_numBitsForChildShapeKey;
}

inline const hkArray<hkpStaticCompoundShape::Instance>&
hkpStaticCompoundShape::getInstances() const {
    return m_instances;
}

inline void hkpStaticCompoundShape::setInstanceFilterInfo(int instanceId, hkUint32 filterInfo) {
    m_instances[instanceId].m_filterInfo = filterInfo;
}

inline hkUint32 hkpStaticCompoundShape::getInstanceFilterInfo(int instanceId) const {
    return m_instances[instanceId].m_filterInfo;
}

inline void hkpStaticCompoundShape::setInstanceFilterInfoMask(int instanceId,
                                                              hkUint32 filterInfoMask) {
    m_instances[instanceId].m_childFilterInfoMask = filterInfoMask;
}

inline hkUint32 hkpStaticCompoundShape::getInstanceFilterInfoMask(int instanceId) const {
    return m_instances[instanceId].m_childFilterInfoMask;
}

inline void hkpStaticCompoundShape::setInstanceUserData(int instanceId, hkUlong userData) {
    m_instances[instanceId].m_userData = userData;
}

inline hkUlong hkpStaticCompoundShape::getInstanceUserData(int instanceId) const {
    return m_instances[instanceId].m_userData;
}

inline void hkpStaticCompoundShape::setInstanceExtraInfo(int instanceId, hkUint16 instanceInfo) {
    const int maxSize = hkMath::max2(m_instanceExtraInfos.getSize(), instanceId + 1);
    m_instanceExtraInfos.setSize(maxSize);
    m_instanceExtraInfos[instanceId] = instanceInfo;
}

inline hkUint16 hkpStaticCompoundShape::getInstanceExtraInfo(int instanceId) const {
    return m_instanceExtraInfos[instanceId];
}

inline const hkArray<hkUint16>& hkpStaticCompoundShape::getInstanceExtraInfos() const {
    return m_instanceExtraInfos;
}

inline void hkpStaticCompoundShape::setInstanceEnabled(int instanceId, hkBool32 isEnabled) {
    Instance& instance = m_instances[instanceId];
    hkUint32 flags = instance.getFlags();
    flags =
        (isEnabled ? (flags & ~Instance::FLAG_IS_DISABLED) : (flags | Instance::FLAG_IS_DISABLED));
    instance.setFlags(flags);
}

inline hkBool32 hkpStaticCompoundShape::isInstanceEnabled(int instanceId) const {
    return !(m_instances[instanceId].getFlags() & Instance::FLAG_IS_DISABLED);
}
