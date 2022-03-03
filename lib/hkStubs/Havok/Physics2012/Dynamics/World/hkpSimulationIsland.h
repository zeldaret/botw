#pragma once

#include <Havok/Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Agent3/Machine/Nn/hkpAgentNnTrack.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintOwner.h>

class hkUnionFind;
class hkpAction;

extern const hkClass hkpSimulationIslandClass;

class hkpSimulationIsland : public hkpConstraintOwner {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpSimulationIsland)

    inline const hkArray<hkpEntity*>& getEntities() const;
    inline const hkArray<hkpAction*>& getActions() const;

    inline hkBool wasActiveLastFrame() const;
    inline hkBool isFixed() const;
    bool isFullyConnected();

    inline hkpWorld* getWorld();

    inline int getMemUsageForIntegration();

    const hkClass* getClassType() const override { return &hkpSimulationIslandClass; }

protected:
    friend class hkpAddModifierUtil;
    friend class hkpContinuousSimulation;
    friend class hkpSimulation;
    friend class hkpWorld;
    friend class hkpWorldCallbackUtil;
    friend class hkpWorldOperationUtil;

    explicit hkpSimulationIsland(hkpWorld* world);
    ~hkpSimulationIsland();

    void internalAddEntity(hkpEntity* entity);
    void internalRemoveEntity(hkpEntity* entity);

    void addConstraintToCriticalLockedIsland(hkpConstraintInstance* constraint) override;
    void removeConstraintFromCriticalLockedIsland(hkpConstraintInstance* constraint) override;
    void addCallbackRequest(hkpConstraintInstance* constraint, int request) override;

    void addAction(hkpAction* act);
    void removeAction(hkpAction* act);

    bool isFullyConnected(hkUnionFind& checkConnectivityOut);

public:
    inline int getStorageIndex();

    void markForWrite();
    inline void unmarkForWrite();

    void isValid();

    void mergeConstraintInfo(hkpSimulationIsland& other);

    inline void markAllEntitiesReadOnly() const;
    inline void unmarkAllEntitiesReadOnly() const;

    hkMultiThreadCheck& getMultiThreadCheck() const { return m_multiThreadCheck; }

    inline hkpAgentNnTrack* getAgentNnTrack(hkpAgentNnTrackType nnTrackType);

public:
    hkpWorld* m_world;
    int m_numConstraints;
    hkObjectIndex m_storageIndex;
    hkObjectIndex m_dirtyListIndex;
    hkUchar m_splitCheckFrameCounter;
    bool m_splitCheckRequested : 2;
    bool m_isSparse : 2;
    bool m_actionListCleanupNeeded : 2;
    bool m_allowIslandLocking : 2;
    bool m_isInActiveIslandsArray : 2;
    bool m_activeMark : 2;
    bool m_tryToIncreaseIslandSizeMark : 2;
    bool m_inIntegrateJob : 2;

protected:
    mutable hkMultiThreadCheck m_multiThreadCheck;

public:
    hkReal m_timeSinceLastHighFrequencyCheck;
    hkReal m_timeSinceLastLowFrequencyCheck;

    hkArray<hkpAction*> m_actions;

    hkTime m_timeOfDeactivation;

    hkInplaceArray<hkpEntity*, 1> m_entities;
    hkpAgentNnTrack m_midphaseAgentTrack;
    hkpAgentNnTrack m_narrowphaseAgentTrack;
};

inline const hkArray<hkpEntity*>& hkpSimulationIsland::getEntities() const {
    return m_entities;
}

inline const hkArray<hkpAction*>& hkpSimulationIsland::getActions() const {
    return m_actions;
}

inline hkBool hkpSimulationIsland::wasActiveLastFrame() const {
    return m_isInActiveIslandsArray;
}

inline hkBool hkpSimulationIsland::isFixed() const {
    return m_storageIndex == HK_INVALID_OBJECT_INDEX;
}

inline hkpWorld* hkpSimulationIsland::getWorld() {
    return m_world;
}

inline int hkpSimulationIsland::getStorageIndex() {
    return m_storageIndex;
}

inline void hkpSimulationIsland::unmarkForWrite() {
    m_multiThreadCheck.unmarkForWrite();
}

inline void hkpSimulationIsland::markAllEntitiesReadOnly() const {}

inline void hkpSimulationIsland::unmarkAllEntitiesReadOnly() const {}

inline hkpAgentNnTrack* hkpSimulationIsland::getAgentNnTrack(hkpAgentNnTrackType nnTrackType) {
    return nnTrackType == HK_AGENT3_NARROWPHASE_TRACK ? &m_narrowphaseAgentTrack :
                                                        &m_midphaseAgentTrack;
}
