#pragma once

#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidableQualityType.h>
#include <Havok/Physics2012/Collide/BroadPhase/hkpBroadPhaseHandle.h>

class hkpTypedBroadPhaseHandle : public hkpBroadPhaseHandle {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpTypedBroadPhaseHandle)

    explicit hkpTypedBroadPhaseHandle(hkFinishLoadedObjectFlag flag) : hkpBroadPhaseHandle(flag) {}

    HK_FORCE_INLINE explicit hkpTypedBroadPhaseHandle(int type);
    HK_FORCE_INLINE hkpTypedBroadPhaseHandle(void* owner, int type);

    /// See hkpWorldObject::BroadPhaseType.
    HK_FORCE_INLINE int getType() const;
    HK_FORCE_INLINE void* getOwner() const;
    HK_FORCE_INLINE void setOwner(void* o);

protected:
    friend class hkpBroadPhaseBorder;

    inline void setType(int type);

    static constexpr int OFFSET_INVALID = 127;
    hkInt8 m_type;
    hkInt8 m_ownerOffset;

public:
    hkInt8 m_objectQualityType;
    hkUint32 m_collisionFilterInfo;
};

inline hkpTypedBroadPhaseHandle::hkpTypedBroadPhaseHandle(int type) {
    m_type = static_cast<hkInt8>(type);
    m_collisionFilterInfo = 0;
    m_objectQualityType = HK_COLLIDABLE_QUALITY_INVALID;
    m_ownerOffset = OFFSET_INVALID;
}

inline hkpTypedBroadPhaseHandle::hkpTypedBroadPhaseHandle(void* owner, int type) {
    m_type = static_cast<hkInt8>(type);
    m_collisionFilterInfo = 0;
    m_objectQualityType = HK_COLLIDABLE_QUALITY_INVALID;
    setOwner(owner);
}

inline int hkpTypedBroadPhaseHandle::getType() const {
    return m_type;
}

inline void* hkpTypedBroadPhaseHandle::getOwner() const {
    return const_cast<char*>(reinterpret_cast<const char*>(this) + m_ownerOffset);
}

inline void hkpTypedBroadPhaseHandle::setOwner(void* o) {
    auto offset = int(hkGetByteOffset(this, o));
    m_ownerOffset = static_cast<hkInt8>(offset);
}

inline void hkpTypedBroadPhaseHandle::setType(int type) {
    m_type = static_cast<hkInt8>(type);
}
