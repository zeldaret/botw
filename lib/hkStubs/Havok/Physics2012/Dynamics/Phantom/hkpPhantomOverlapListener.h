#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpPhantom;
class hkpCollidable;

enum hkpCollidableAccept {
    HK_COLLIDABLE_ACCEPT = 0,
    HK_COLLIDABLE_REJECT = 1,
};

struct hkpCollidableAddedEvent {
    HK_DECLARE_CLASS_ALLOCATOR(hkpCollidableAddedEvent)

    const hkpPhantom* m_phantom;
    const hkpCollidable* m_collidable;
    mutable hkpCollidableAccept m_collidableAccept;
};

struct hkpCollidableRemovedEvent {
    HK_DECLARE_CLASS_ALLOCATOR(hkpCollidableRemovedEvent)

    const hkpPhantom* m_phantom;
    const hkpCollidable* m_collidable;
    hkBool m_collidableWasAdded;
};

class hkpPhantomOverlapListener {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpPhantomOverlapListener)

    virtual void collidableAddedCallback(const hkpCollidableAddedEvent& event) = 0;

    virtual void collidableRemovedCallback(const hkpCollidableRemovedEvent& event) = 0;

    virtual ~hkpPhantomOverlapListener() = default;
};
