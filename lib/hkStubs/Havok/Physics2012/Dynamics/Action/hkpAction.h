#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkStepInfo;
class hkpEntity;
class hkpSimulationIsland;
class hkpPhantom;
class hkpWorld;

class hkpAction : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpAction)
    HK_DECLARE_REFLECTION()

    inline explicit hkpAction(hkUlong userData);
    explicit hkpAction(hkFinishLoadedObjectFlag flag) : hkReferencedObject(flag), m_name(flag) {}

    ~hkpAction() override = default;

    virtual void applyAction(const hkStepInfo& stepInfo) = 0;
    virtual void getEntities(hkArray<hkpEntity*>& entitiesOut) = 0;
    virtual void getPhantoms(hkArray<hkpPhantom*>& phantomsOut) {}

    inline hkpWorld* getWorld();

    virtual void entityRemovedCallback(hkpEntity* entity) = 0;

    inline hkUlong getUserData() const;
    inline void setUserData(hkUlong data);

    inline const char* getName() const;
    inline void setName(const char* name);

    virtual hkpAction* clone(const hkArray<hkpEntity*>& newEntities,
                             const hkArray<hkpPhantom*>& newPhantoms) const = 0;

    // For internal use.
    inline hkpSimulationIsland* getSimulationIsland();
    inline void setSimulationIsland(hkpSimulationIsland* island);
    inline void setWorld(hkpWorld* owner);

private:
    hkpWorld* m_world;
    hkpSimulationIsland* m_island;

protected:
    friend class hkpWorld;
    friend class hkpWorldOperationUtil;
    friend class hkpSimulationIsland;

    hkUlong m_userData;
    hkStringPtr m_name;
};

inline hkpAction::hkpAction(hkUlong userData)
    : m_world(nullptr), m_island(nullptr), m_userData(userData) {}

inline hkpWorld* hkpAction::getWorld() {
    return m_world;
}

inline hkUlong hkpAction::getUserData() const {
    return m_userData;
}

inline void hkpAction::setUserData(hkUlong data) {
    m_userData = data;
}

inline const char* hkpAction::getName() const {
    return m_name;
}

inline void hkpAction::setName(const char* name) {
    m_name = name;
}

inline hkpSimulationIsland* hkpAction::getSimulationIsland() {
    return m_island;
}

inline void hkpAction::setSimulationIsland(hkpSimulationIsland* isl) {
    m_island = isl;
}

inline void hkpAction::setWorld(hkpWorld* owner) {
    m_world = owner;
}
