#pragma once

#include <Havok/Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Agent3/Machine/Nn/hkpLinkedCollidable.h>
#include <Havok/Physics2012/Dynamics/Common/hkpProperty.h>

class hkpShapeModifier;
class hkpWorld;

namespace hkWorldOperation {
enum Result {
    POSTPONED,
    DONE,
};
}  // namespace hkWorldOperation

class hkpWorldObject : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpWorldObject)
    HK_DECLARE_REFLECTION()

    enum BroadPhaseType {
        BROAD_PHASE_INVALID,
        /// hkpEntity
        BROAD_PHASE_ENTITY,
        /// hkpPhantom
        BROAD_PHASE_PHANTOM,
        /// hkpBroadPhaseBorder's objects (AABB phantoms)
        BROAD_PHASE_BORDER,
        BROAD_PHASE_MAX_ID
    };

    enum MtChecks {
        MULTI_THREADING_CHECKS_ENABLE,
        MULTI_THREADING_CHECKS_IGNORE,
    };

    explicit hkpWorldObject(hkFinishLoadedObjectFlag flag);

    void addProperty(hkUint32 key, hkpPropertyValue value);
    hkpPropertyValue removeProperty(hkUint32 key);
    void setProperty(hkUint32 key, hkpPropertyValue value);
    void editProperty(hkUint32 key, hkpPropertyValue value,
                      MtChecks mtCheck = MULTI_THREADING_CHECKS_ENABLE);
    inline hkpPropertyValue getProperty(hkUint32 key,
                                        MtChecks mtCheck = MULTI_THREADING_CHECKS_ENABLE) const;
    inline bool hasProperty(hkUint32 key, MtChecks mtCheck = MULTI_THREADING_CHECKS_ENABLE) const;
    void lockProperty(hkUint32 key);
    void unlockProperty(hkUint32 key);
    inline void clearAndDeallocateProperties();

    inline hkpCollidable* getCollidableRw();
    inline const hkpCollidable* getCollidable() const;
    inline hkpLinkedCollidable* getLinkedCollidable();
    inline const hkpLinkedCollidable* getLinkedCollidable() const;
    inline const hkpLinkedCollidable* getCollidableMtUnchecked() const;

    inline hkBool isAddedToWorld() const;
    inline hkpWorld* getWorld() const;

    inline hkUlong getUserData() const;
    inline void setUserData(hkUlong data);

    inline const char* getName() const;
    inline void setName(const char* name);

    virtual hkWorldOperation::Result setShape(const hkpShape* shape);
    virtual hkWorldOperation::Result updateShape(hkpShapeModifier* shapeModifier);

    inline hkMultiThreadCheck& getMultiThreadCheck();
    inline void markForRead();
    inline void markForWrite();
    void markForWriteImpl();
    inline void unmarkForRead();
    inline void unmarkForWrite();

    void checkReadWrite();
    void checkReadOnly() const;

    inline ~hkpWorldObject() override;

    virtual class hkMotionState* getMotionState() = 0;

    inline void copyProperties(const hkpWorldObject* otherObj);

protected:
    friend class hkpWorld;
    friend class hkpWorldOperationUtil;
    inline void setWorld(hkpWorld* world);

    hkpWorldObject(const hkpShape* shape, BroadPhaseType type);

    hkpWorld* m_world;
    hkUlong m_userData;
    hkpLinkedCollidable m_collidable;
    hkMultiThreadCheck m_multiThreadCheck;
    hkStringPtr m_name;

public:
    hkArray<hkpProperty> m_properties;
};

inline hkpWorldObject* hkpGetWorldObject(const hkpCollidable* collidable) {
    return reinterpret_cast<hkpWorldObject*>(const_cast<void*>(collidable->getOwner()));
}

inline hkpPropertyValue hkpWorldObject::getProperty(hkUint32 key, hkpWorldObject::MtChecks) const {
    for (int i = 0; i < m_properties.getSize(); ++i) {
        if (m_properties[i].m_key == key) {
            return m_properties[i].m_value;
        }
    }
    return 0;
}

inline bool hkpWorldObject::hasProperty(hkUint32 key, hkpWorldObject::MtChecks) const {
    for (int i = 0; i < m_properties.getSize(); ++i) {
        if (m_properties[i].m_key == key) {
            return true;
        }
    }
    return false;
}

inline void hkpWorldObject::clearAndDeallocateProperties() {
    m_properties.clearAndDeallocate();
}

inline hkpCollidable* hkpWorldObject::getCollidableRw() {
    return &m_collidable;
}

inline const hkpCollidable* hkpWorldObject::getCollidable() const {
    return &m_collidable;
}

inline hkpLinkedCollidable* hkpWorldObject::getLinkedCollidable() {
    return &m_collidable;
}

inline const hkpLinkedCollidable* hkpWorldObject::getLinkedCollidable() const {
    return &m_collidable;
}

inline const hkpLinkedCollidable* hkpWorldObject::getCollidableMtUnchecked() const {
    return &m_collidable;
}

inline hkBool hkpWorldObject::isAddedToWorld() const {
    return m_world != nullptr;
}

inline hkpWorld* hkpWorldObject::getWorld() const {
    return m_world;
}

inline hkUlong hkpWorldObject::getUserData() const {
    return m_userData;
}

inline void hkpWorldObject::setUserData(hkUlong data) {
    m_userData = data;
}

inline const char* hkpWorldObject::getName() const {
    return m_name;
}

inline void hkpWorldObject::setName(const char* name) {
    m_name = name;
}

inline hkMultiThreadCheck& hkpWorldObject::getMultiThreadCheck() {
    return m_multiThreadCheck;
}

inline void hkpWorldObject::markForRead() {
    getMultiThreadCheck().markForRead();
}

inline void hkpWorldObject::markForWrite() {
    getMultiThreadCheck().markForWrite();
}

inline void hkpWorldObject::unmarkForRead() {
    getMultiThreadCheck().unmarkForRead();
}

inline void hkpWorldObject::unmarkForWrite() {
    getMultiThreadCheck().unmarkForWrite();
}

inline hkpWorldObject::~hkpWorldObject() {
    if (m_collidable.getShape()) {
        m_collidable.getShape()->removeReference();
    }
}

inline void hkpWorldObject::copyProperties(const hkpWorldObject* otherObj) {
    m_properties = otherObj->m_properties;
}

inline void hkpWorldObject::setWorld(hkpWorld* world) {
    m_world = world;
}
