#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Dispatch/BroadPhase/hkpBroadPhaseListener.h>

class hkpPhantomBroadPhaseListener : public hkReferencedObject, public hkpBroadPhaseListener {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpPhantomBroadPhaseListener)

    hkpPhantomBroadPhaseListener() = default;

    void addCollisionPair(hkpTypedBroadPhaseHandlePair& pair) override;
    void removeCollisionPair(hkpTypedBroadPhaseHandlePair& pair) override;
};
