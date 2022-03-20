#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Phantom/hkpPhantomOverlapListener.h>
#include <Havok/Physics2012/Dynamics/Phantom/hkpPhantomType.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorldObject.h>

class hkpPhantomListener;
class hkpPhantomOverlapListener;

class hkpPhantom : public hkpWorldObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpPhantom)
    HK_DECLARE_REFLECTION()

    explicit hkpPhantom(hkFinishLoadedObjectFlag flag) : hkpWorldObject(flag) {}
    ~hkpPhantom() override;

    virtual hkpPhantomType getType() const = 0;

    virtual void calcAabb(hkAabb& aabb) = 0;

    virtual void addOverlappingCollidable(hkpCollidable* collidable) = 0;

    virtual hkBool isOverlappingCollidableAdded(const hkpCollidable* collidable) = 0;

    virtual void removeOverlappingCollidable(hkpCollidable* collidable) = 0;

    virtual void ensureDeterministicOrder() = 0;

    virtual hkpPhantom* clone() const = 0;

    void addPhantomListener(hkpPhantomListener* el);
    void removePhantomListener(hkpPhantomListener* el);

    void addPhantomOverlapListener(hkpPhantomOverlapListener* el);
    void removePhantomOverlapListener(hkpPhantomOverlapListener* el);

    inline const hkArray<hkpPhantomListener*>& getPhantomListeners() const;
    inline const hkArray<hkpPhantomOverlapListener*>& getPhantomOverlapListeners() const;

    virtual void updateShapeCollectionFilter() {}

    void updateBroadPhase(const hkAabb& aabb);
    void setBoundingVolumeData(const hkAabb& aabb);

    void firePhantomAdded();
    void firePhantomRemoved();
    void firePhantomShapeSet();

protected:
    inline explicit hkpPhantom(const hkpShape* shape);

    inline hkpCollidableAccept fireCollidableAdded(const hkpCollidable* collidable);
    inline void fireCollidableRemoved(const hkpCollidable* collidable, hkBool collidableWasAdded);
    void firePhantomDeleted();

    hkArray<hkpPhantomOverlapListener*> m_overlapListeners;
    hkArray<hkpPhantomListener*> m_phantomListeners;

    friend class hkpPhantomBatchMoveUtil;

    void removeNullOverlapListeners();
    void removeNullPhantomListeners();

public:
    // Internal.
    virtual void deallocateInternalArrays();
};

inline hkpPhantom* hkpGetPhantom(const hkpCollidable* collidable) {
    if (collidable->getType() == hkpWorldObject::BROAD_PHASE_PHANTOM)
        return static_cast<hkpPhantom*>(hkpGetWorldObject(collidable));
    return nullptr;
}

inline const hkArray<hkpPhantomListener*>& hkpPhantom::getPhantomListeners() const {
    return m_phantomListeners;
}

inline const hkArray<hkpPhantomOverlapListener*>& hkpPhantom::getPhantomOverlapListeners() const {
    return m_overlapListeners;
}

inline hkpPhantom::hkpPhantom(const hkpShape* shape) : hkpWorldObject(shape, BROAD_PHASE_PHANTOM) {
    m_collidable.setOwner(this);
}

inline hkpCollidableAccept hkpPhantom::fireCollidableAdded(const hkpCollidable* collidable) {
    hkpCollidableAddedEvent event;
    event.m_collidable = collidable;
    event.m_phantom = this;
    event.m_collidableAccept = HK_COLLIDABLE_ACCEPT;

    for (int i = m_overlapListeners.getSize() - 1; i >= 0; i--) {
        if (m_overlapListeners[i])
            m_overlapListeners[i]->collidableAddedCallback(event);
    }
    return event.m_collidableAccept;
}

inline void hkpPhantom::fireCollidableRemoved(const hkpCollidable* collidable,
                                              hkBool collidableWasAdded) {
    hkpCollidableRemovedEvent event;
    event.m_collidable = collidable;
    event.m_phantom = this;
    event.m_collidableWasAdded = collidableWasAdded;

    for (int i = m_overlapListeners.getSize() - 1; i >= 0; i--) {
        if (m_overlapListeners[i])
            m_overlapListeners[i]->collidableRemovedCallback(event);
    }
}
