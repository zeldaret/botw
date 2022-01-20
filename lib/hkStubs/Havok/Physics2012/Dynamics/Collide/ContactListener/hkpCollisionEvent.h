#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/World/hkpSimulationIsland.h>

class hkpSimpleConstraintContactMgr;

class hkpCollisionEvent {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCollisionEvent)

    enum CallbackSource {
        SOURCE_A = 0,
        SOURCE_B = 1,
        SOURCE_WORLD,
    };

    inline hkpCollisionEvent(CallbackSource source, hkpRigidBody* bodyA, hkpRigidBody* bodyB,
                             hkpSimpleConstraintContactMgr* mgr);

    inline hkpRigidBody* getBody(int bodyIdx) const;
    inline hkpSimulationIsland* getSimulationIsland() const;

    CallbackSource m_source;
    hkpRigidBody* m_bodies[2];
    hkpSimpleConstraintContactMgr* m_contactMgr;
};

inline hkpCollisionEvent::hkpCollisionEvent(hkpCollisionEvent::CallbackSource source,
                                            hkpRigidBody* bodyA, hkpRigidBody* bodyB,
                                            hkpSimpleConstraintContactMgr* mgr)
    : m_source(source), m_bodies{bodyA, bodyB}, m_contactMgr(mgr) {}

inline hkpRigidBody* hkpCollisionEvent::getBody(int bodyIdx) const {
    return m_bodies[bodyIdx];
}

inline hkpSimulationIsland* hkpCollisionEvent::getSimulationIsland() const {
    auto* island = m_bodies[0]->getSimulationIsland();
    if (island->isFixed()) {
        island = m_bodies[1]->getSimulationIsland();
    }
    return island;
}
