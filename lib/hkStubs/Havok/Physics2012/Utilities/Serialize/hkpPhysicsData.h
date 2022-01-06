#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/World/hkpPhysicsSystem.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorldCinfo.h>

class hkpRigidBody;
class hkpWorld;

class hkpPhysicsData : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpPhysicsData)
    HK_DECLARE_REFLECTION()

    hkpPhysicsData();
    explicit hkpPhysicsData(hkFinishLoadedObjectFlag f) : hkReferencedObject(f), m_systems(f) {}

    ~hkpPhysicsData() override;

    inline hkpWorldCinfo* getWorldCinfo();
    inline void setWorldCinfo(hkpWorldCinfo* info);

    inline void addPhysicsSystem(hkpPhysicsSystem* system);
    inline void removePhysicsSystem(int i);
    inline const hkArray<hkpPhysicsSystem*>& getPhysicsSystems() const;

    hkpPhysicsSystem* findPhysicsSystemByName(const char* name) const;
    /// Look for a rigid body by name (case insensitive)
    hkpRigidBody* findRigidBodyByName(const char* name) const;

    void populateFromWorld(const hkpWorld* world, bool saveContactPoints = false);

    hkpWorld* createWorld(hkBool registerAllAgents = true);

    struct SplitPhysicsSystemsOutput {
        HK_DECLARE_CLASS_ALLOCATOR(hkpPhysicsData::SplitPhysicsSystemsOutput)

        hkpPhysicsSystem* m_unconstrainedFixedBodies;
        hkpPhysicsSystem* m_unconstrainedKeyframedBodies;
        hkpPhysicsSystem* m_unconstrainedMovingBodies;
        hkpPhysicsSystem* m_phantoms;
        hkArray<hkpPhysicsSystem*> m_constrainedSystems;
    };

    static void splitPhysicsSystems(const hkpPhysicsSystem* inputSystemConst,
                                    SplitPhysicsSystemsOutput& output);

protected:
    hkpWorldCinfo* m_worldCinfo;
    hkArray<hkpPhysicsSystem*> m_systems;
};

inline hkpWorldCinfo* hkpPhysicsData::getWorldCinfo() {
    return m_worldCinfo;
}

inline void hkpPhysicsData::setWorldCinfo(hkpWorldCinfo* info) {
    if (info != nullptr)
        info->addReference();
    if (m_worldCinfo != nullptr)
        m_worldCinfo->removeReference();

    m_worldCinfo = info;
}

inline void hkpPhysicsData::addPhysicsSystem(hkpPhysicsSystem* system) {
    system->addReference();
    m_systems.pushBack(system);
}

inline void hkpPhysicsData::removePhysicsSystem(int i) {
    m_systems[i]->removeReference();
    m_systems.removeAt(i);
}

inline const hkArray<hkpPhysicsSystem*>& hkpPhysicsData::getPhysicsSystems() const {
    return m_systems;
}
