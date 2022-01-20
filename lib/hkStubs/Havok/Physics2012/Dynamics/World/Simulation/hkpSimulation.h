#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorld.h>

class hkpAgentNnEntry;
class hkpConstraintQueryIn;
class hkpProcessCollisionOutput;
class hkpWorld;

class hkpSimulation : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpSimulation)
    HK_DECLARE_REFLECTION()

    enum FindContacts {
        FIND_CONTACTS_DEFAULT = 0,
        FIND_CONTACTS_EXTRA,
    };

    enum ResetCollisionInformation {
        RESET_TOI = 1,
        RESET_TIM = 2,
        RESET_AABB = 4,
        RESET_ALL = 7,
    };

    using AgentEntryProcessFunction = void (hkpSimulation::*)(hkpAgentNnEntry*,
                                                              const hkpProcessCollisionInput&,
                                                              hkpProcessCollisionOutput&);

    explicit hkpSimulation(hkpWorld* world);
    explicit hkpSimulation(hkFinishLoadedObjectFlag flag) : hkReferencedObject(flag) {}
    ~hkpSimulation() override;

    virtual hkpStepResult stepDeltaTime(hkReal physicsDeltaTime);
    virtual hkpStepResult integrate(hkReal physicsDeltaTime);
    virtual hkpStepResult collide();
    virtual hkpStepResult advanceTime();

    void setFrameTimeMarker(hkReal frameDeltaTime);
    bool isSimulationAtMarker();
    bool isSimulationAtPsi() const;

    virtual hkpStepResult stepBeginSt(hkJobQueue* queue, hkReal physicsDeltaTime) {
        return HK_STEP_RESULT_SUCCESS;
    }

    virtual hkpStepResult finishMtStep(hkJobQueue* queue, hkThreadPool* threadPool) {
        return HK_STEP_RESULT_SUCCESS;
    }

    virtual void getMultithreadConfig(hkpMultithreadConfig& config) {}
    virtual void setMultithreadConfig(const hkpMultithreadConfig& config, hkJobQueue* queue) {}

    hkpWorld* getWorld() const { return m_world; }

    hkReal getCurrentTime() const { return m_currentTime; }
    hkReal getCurrentPsiTime() const { return m_currentPsiTime; }
    hkReal getSimulateUntilTime() const { return m_simulateUntilTime; }
    hkReal getPhysicsDeltaTime() const { return m_physicsDeltaTime; }
    hkReal getFrameMarkerPsiSnap() const { return m_frameMarkerPsiSnap; }

    virtual void collideEntitiesDiscrete(hkpEntity** entities, int numEntities, hkpWorld* world,
                                         const hkStepInfo& stepInfo,
                                         FindContacts findExtraContacts);

    static void collideEntitiesBroadPhaseDiscrete(hkpEntity** entities, int numEntities,
                                                  hkpWorld* world);

    void collideEntitiesNarrowPhaseDiscrete(hkpEntity** entities, int numEntities,
                                            const hkpProcessCollisionInput& input,
                                            FindContacts findExtraContacts);

    virtual void
    resetCollisionInformationForEntities(hkpEntity** entities, int numEntities, hkpWorld* world,
                                         enum ResetCollisionInformation resetInfo = RESET_ALL);

    virtual void assertThereIsNoCollisionInformationForEntities(hkpEntity** entities,
                                                                int numEntities, hkpWorld* world) {}

    virtual void removeCollisionInformationForAgent(hkpAgentNnEntry* agent) {}

    virtual void assertThereIsNoCollisionInformationForAgent(hkpAgentNnEntry* agent) {}

protected:
    friend class hkpWorld;
    friend class hkpWorldOperationQueue;
    friend class hkpWorldMemoryUtil;

    virtual void reintegrateAndRecollideEntities(hkpEntity** entityBatch, int numEntities,
                                                 hkpWorld* world, int reintegrateRecollideMode);

    void checkDeltaTimeIsOk(hkReal deltaTime);
    hkpStepResult reCollideAfterStepFailure();
    virtual void collideInternal(const hkStepInfo& stepInfoIn);
    hkpStepResult integrateInternal(const hkStepInfo& stepInfoIn);
    void applyActions();

    static void integrateIsland(hkpSimulationIsland* isle, const hkpWorldDynamicsStepInfo& stepInfo,
                                hkpConstraintQueryIn& constraintQueryIn);

    static void collideIslandNarrowPhaseDiscrete(hkpSimulationIsland* isle,
                                                 const hkpProcessCollisionInput& input);

    hkReal snapSimulateTimeAndGetTimeToAdvanceTo();

    void processAgentsOfEntities(hkpEntity** entities, int numEntities,
                                 const hkpProcessCollisionInput& input,
                                 AgentEntryProcessFunction processingFunction,
                                 FindContacts findExtraContacts);

    void processAgentCollideDiscrete(hkpAgentNnEntry* entry,
                                     const hkpProcessCollisionInput& processInput,
                                     hkpProcessCollisionOutput& processOutput);

    void processAgentResetCollisionInformation(hkpAgentNnEntry* entry,
                                               const hkpProcessCollisionInput& processInput,
                                               hkpProcessCollisionOutput& processOutput);

public:
    virtual void warpTime(hkReal deltaTime) {}

    void setCurrentTime(hkTime time) { m_currentTime = time; }
    void setCurrentPsiTime(hkTime time) { m_currentPsiTime = time; }
    void setSimulateUntilTime(hkTime time) { m_simulateUntilTime = time; }

protected:
    enum LastProcessingStep { INTEGRATE, COLLIDE };

    hkUint32 m_determinismCheckFrameCounter;
    hkpWorld* m_world;
    hkEnum<LastProcessingStep, hkUint8> m_lastProcessingStep;
    hkTime m_currentTime;
    hkTime m_currentPsiTime;
    hkReal m_physicsDeltaTime;
    hkTime m_simulateUntilTime;
    hkReal m_frameMarkerPsiSnap;
    hkUint32 m_previousStepResult;
};
