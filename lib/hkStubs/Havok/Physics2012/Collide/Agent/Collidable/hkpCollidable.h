#pragma once

#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCdBody.h>
#include <Havok/Physics2012/Collide/BroadPhase/hkpTypedBroadPhaseHandle.h>

class hkAabbUint32;

class hkpCollidable : public hkpCdBody {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCollidable)

    struct BoundingVolumeData {
        HK_DECLARE_CLASS_ALLOCATOR(hkpCollidable::BoundingVolumeData)

        BoundingVolumeData();
        explicit inline BoundingVolumeData(hkFinishLoadedObjectFlag flag);

        HK_FORCE_INLINE bool hasAllocations() const;
        void deallocate();
        void allocate(int numChildShapes);

        HK_FORCE_INLINE void invalidate() {
            m_min[0] = 1;
            m_max[0] = 0;
        }
        HK_FORCE_INLINE bool isValid() const { return m_min[0] <= m_max[0]; }

        hkUint32 m_min[3];
        hkUint8 m_expansionMin[3];
        hkUint8 m_expansionShift;
        hkUint32 m_max[3];
        hkUint8 m_expansionMax[3];
        hkUint8 m_padding;
        hkUint16 m_numChildShapeAabbs;
        hkUint16 m_capacityChildShapeAabbs;
        hkAabbUint32* m_childShapeAabbs;
        hkpShapeKey* m_childShapeKeys;
    };

    enum ForceCollideOntoPpuReasons {
        FORCE_PPU_USER_REQUEST = 1,
        FORCE_PPU_SHAPE_REQUEST = 2,
        FORCE_PPU_MODIFIER_REQUEST = 4,
        FORCE_PPU_SHAPE_UNCHECKED = 8,
    };

    explicit hkpCollidable(hkFinishLoadedObjectFlag flag);
    inline hkpCollidable(const hkpShape* shape, const hkTransform* t, int type = 0);
    inline hkpCollidable(const hkpShape* shape, const hkMotionState* ms, int type = 0);
    inline ~hkpCollidable();

    inline void setShape(const hkpShape* shape);

    inline void* getOwner() const;
    inline void setOwner(void* owner);

    inline hkpCollidableQualityType getQualityType() const;
    inline void setQualityType(hkpCollidableQualityType type);

    inline hkReal getAllowedPenetrationDepth() const;
    inline void setAllowedPenetrationDepth(hkReal val);

    inline hkUint32 getCollisionFilterInfo() const;
    inline void setCollisionFilterInfo(hkUint32 info);

    /// @see hkpWorldObject::BroadPhaseType
    inline int getType() const;

protected:
    hkInt8 m_ownerOffset;

public:
    hkUint8 m_forceCollideOntoPpu;
    hkUint16 m_shapeSizeOnSpu;
    hkpTypedBroadPhaseHandle m_broadPhaseHandle;
    BoundingVolumeData m_boundingVolumeData;
    hkReal m_allowedPenetrationDepth;
};

inline hkpCollidable::hkpCollidable(hkFinishLoadedObjectFlag flag)
    : m_broadPhaseHandle(flag), m_boundingVolumeData(flag) {
    if (flag.m_finishing) {
        m_broadPhaseHandle.setOwner(this);
    }
}

inline hkpCollidable::hkpCollidable(const hkpShape* shape, const hkTransform* t, int type)
    : hkpCdBody(shape, t), m_ownerOffset(0), m_broadPhaseHandle(type),
      m_allowedPenetrationDepth(hkReal(-1)) {
    m_broadPhaseHandle.setOwner(this);
    m_forceCollideOntoPpu = hkpCollidable::FORCE_PPU_SHAPE_UNCHECKED;
    m_shapeSizeOnSpu = 0;
}

inline hkpCollidable::hkpCollidable(const hkpShape* shape, const hkMotionState* ms, int type)
    : hkpCdBody(shape, ms), m_ownerOffset(0), m_broadPhaseHandle(type),
      m_allowedPenetrationDepth(hkReal(-1)) {
    m_broadPhaseHandle.setOwner(this);
    m_forceCollideOntoPpu = hkpCollidable::FORCE_PPU_SHAPE_UNCHECKED;
    m_shapeSizeOnSpu = 0;
}

inline hkpCollidable::~hkpCollidable() {}

inline void hkpCollidable::setShape(const hkpShape* shape) {
    m_shape = shape;
}

inline void* hkpCollidable::getOwner() const {
    return const_cast<char*>(reinterpret_cast<const char*>(this) + m_ownerOffset);
}

inline void hkpCollidable::setOwner(void* owner) {
    auto ownerOffset = int(hkGetByteOffset(this, owner));
    m_ownerOffset = static_cast<hkInt8>(ownerOffset);
}

inline hkpCollidableQualityType hkpCollidable::getQualityType() const {
    return hkpCollidableQualityType(m_broadPhaseHandle.m_objectQualityType);
}

inline void hkpCollidable::setQualityType(hkpCollidableQualityType type) {
    m_broadPhaseHandle.m_objectQualityType = type;
}

inline hkReal hkpCollidable::getAllowedPenetrationDepth() const {
    return m_allowedPenetrationDepth;
}

inline void hkpCollidable::setAllowedPenetrationDepth(hkReal val) {
    m_allowedPenetrationDepth = val;
}

inline hkUint32 hkpCollidable::getCollisionFilterInfo() const {
    return m_broadPhaseHandle.m_collisionFilterInfo;
}

inline void hkpCollidable::setCollisionFilterInfo(hkUint32 info) {
    m_broadPhaseHandle.m_collisionFilterInfo = info;
}

inline int hkpCollidable::getType() const {
    return m_broadPhaseHandle.getType();
}

inline hkpCollidable::BoundingVolumeData::BoundingVolumeData(hkFinishLoadedObjectFlag flag) {
    if (flag.m_finishing) {
        m_numChildShapeAabbs = 0;
        m_capacityChildShapeAabbs = 0;
        m_childShapeAabbs = nullptr;
        m_childShapeKeys = nullptr;
        invalidate();
    }
}

inline bool hkpCollidable::BoundingVolumeData::hasAllocations() const {
    return m_childShapeAabbs != nullptr;
}
