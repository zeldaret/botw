#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Phantom/hkpPhantomOverlapListener.h>
#include <Havok/Physics2012/Dynamics/World/Listener/hkpWorldDeletionListener.h>
#include <Havok/Physics2012/Dynamics/World/Listener/hkpWorldPostSimulationListener.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorldCinfo.h>

class hkpEntity;
class hkpPhantom;
class hkpWorld;

class hkpBroadPhaseBorder : public hkReferencedObject,
                            protected hkpWorldDeletionListener,
                            protected hkpPhantomOverlapListener,
                            protected hkpWorldPostSimulationListener {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpBroadPhaseBorder)

    hkpBroadPhaseBorder(
        hkpWorld* world,
        hkpWorldCinfo::BroadPhaseBorderBehaviour type = hkpWorldCinfo::BROADPHASE_BORDER_ASSERT,
        hkBool postponeAndSortCallbacks = false);

    ~hkpBroadPhaseBorder() override;

    virtual void maxPositionExceededCallback(hkpEntity* body);

    virtual void deactivate();

    void collidableAddedCallback(const hkpCollidableAddedEvent& event) override;
    void collidableRemovedCallback(const hkpCollidableRemovedEvent& event) override;
    void postSimulationCallback(hkpWorld* world) override;
    void worldDeletedCallback(hkpWorld* world) override;

    hkpWorld* m_world;
    hkpPhantom* m_phantoms[6];
    hkpWorldCinfo::BroadPhaseBorderBehaviour m_type;
    hkBool m_postponeAndSortCallbacks;
    hkArray<hkpEntity*> m_entitiesExitingBroadPhase;
};
