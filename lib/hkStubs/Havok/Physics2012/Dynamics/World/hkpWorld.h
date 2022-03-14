#pragma once

#include <Havok/Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h>
#include <Havok/Common/Base/Types/Physics/hkStepInfo.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics/ConstraintSolver/Solve/hkpSolverInfo.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorldCinfo.h>

class hkCriticalSection;
class hkJobQueue;
class hkSemaphoreBusyWait;
class hkThreadPool;
class hkWorldMemoryAvailableWatchDog;
class hkdWorld;
class hknpWorld;
class hkpAction;
class hkpActionListener;
class hkpBodyOperation;
class hkpBroadPhase;
class hkpBroadPhaseBorder;
class hkpBroadPhaseBorderListener;
class hkpCdBodyPairCollector;
class hkpCdPointCollector;
class hkpCollisionDispatcher;
class hkpCollisionFilter;
class hkpConstraintData;
class hkpConstraintInstance;
class hkpConstraintListener;
class hkpContactImpulseLimitBreachedListener;
class hkpContactListener;
class hkpDebugInfoOnPendingOperationQueues;
class hkpEntity;
class hkpEntityEntityBroadPhaseListener;
class hkpEntityListener;
class hkpIslandActivationListener;
class hkpIslandPostCollideListener;
class hkpIslandPostIntegrateListener;
struct hkpLinearCastInput;
class hkpMtThreadStructure;
class hkpMultithreadConfig;
class hkpPhantom;
class hkpPhantomBroadPhaseListener;
class hkpPhantomListener;
class hkpPhysicsSystem;
struct hkpProcessCollisionInput;
class hkpRigidBody;
class hkpSimulation;
class hkpSimulationIsland;
class hkpTypedBroadPhaseDispatcher;
struct hkpViolatedConstraintArray;
class hkpWorldDeletionListener;
class hkpWorldExtension;
struct hkpWorldGetClosestPointsCommand;
struct hkpWorldLinearCastCommand;
class hkpWorldMaintenanceMgr;
class hkpWorldOperationQueue;
class hkpWorldPostCollideListener;
class hkpWorldPostIntegrateListener;
class hkpWorldPostSimulationListener;
struct hkpWorldRayCastCommand;
struct hkpWorldRayCastOutput;

namespace hkWorldOperation {
struct BaseOperation;
class UserCallback;
}  // namespace hkWorldOperation

enum hkpUpdateCollisionFilterOnWorldMode {
    HK_UPDATE_FILTER_ON_WORLD_FULL_CHECK,
    HK_UPDATE_FILTER_ON_WORLD_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY,
};

enum hkpUpdateCollisionFilterOnEntityMode {
    HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK,
    HK_UPDATE_FILTER_ON_ENTITY_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY,
};

enum hkpEntityActivation {
    HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE,
    HK_ENTITY_ACTIVATION_DO_ACTIVATE,
};

enum hkpUpdateCollectionFilterMode {
    HK_UPDATE_COLLECTION_FILTER_IGNORE_SHAPE_COLLECTIONS,
    HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS,
};

enum hkpStepResult {
    HK_STEP_RESULT_SUCCESS,
    HK_STEP_RESULT_MEMORY_FAILURE_BEFORE_INTEGRATION,
    HK_STEP_RESULT_MEMORY_FAILURE_DURING_COLLIDE,
    HK_STEP_RESULT_MEMORY_FAILURE_DURING_TOI_SOLVE,
};

struct hkpWorldDynamicsStepInfo {
    HK_DECLARE_CLASS_ALLOCATOR(hkpWorldDynamicsStepInfo)

    hkStepInfo m_stepInfo;
    hkpSolverInfo m_solverInfo;
};

class hkpWorld : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpWorld)
    HK_DECLARE_REFLECTION()

    enum ReintegrationRecollideMode {
        RR_MODE_REINTEGRATE = 1 << 0,
        RR_MODE_RECOLLIDE_BROADPHASE = 1 << 1,
        RR_MODE_RECOLLIDE_NARROWPHASE = 1 << 2,
        RR_MODE_ALL = (1 << 3) - 1,
    };

    hkpWorld(const hkpWorldCinfo& info, unsigned int sdkversion = 20140200u);
    explicit hkpWorld(hkFinishLoadedObjectFlag flag);
    ~hkpWorld() override;

    void getCinfo(hkpWorldCinfo& info) const;

    void setGravity(const hkVector4& gravity);
    inline const hkVector4& getGravity() const;

    hkTime getCurrentTime() const;
    hkTime getCurrentPsiTime() const;

    // region Entity

    hkpEntity*
    addEntity(hkpEntity* entity,
              hkpEntityActivation initialActivationState = HK_ENTITY_ACTIVATION_DO_ACTIVATE);

    hkBool removeEntity(hkpEntity* entity);

    void
    addEntityBatch(hkpEntity* const* entityBatch, int numEntities,
                   hkpEntityActivation initialActivationState = HK_ENTITY_ACTIVATION_DO_ACTIVATE);

    void removeEntityBatch(hkpEntity* const* entityBatch, int numEntities);

    // endregion

    // region Constraint

    hkpConstraintInstance* addConstraint(hkpConstraintInstance* constraint);
    hkBool removeConstraint(hkpConstraintInstance* constraint);
    hkpConstraintInstance* createAndAddConstraintInstance(hkpRigidBody* bodyA, hkpRigidBody* bodyB,
                                                          hkpConstraintData* constraintData);

    // endregion

    // region Action

    hkpAction* addAction(hkpAction* action);
    void removeAction(hkpAction* action);
    void removeActionImmediately(hkpAction* action);

    // endregion

    // region Phantom

    inline const hkArray<hkpPhantom*>& getPhantoms() const;
    hkpPhantom* addPhantom(hkpPhantom* phantom);
    void addPhantomBatch(hkpPhantom* const* phantomBatch, int numPhantoms);
    void removePhantom(hkpPhantom* phantom);
    void removePhantomBatch(hkpPhantom* const* phantomBatch, int numPhantoms);
    void activateRegion(const hkAabb& aabb);

    // endregion

    // region System

    void addPhysicsSystem(const hkpPhysicsSystem* sys);
    void removePhysicsSystem(const hkpPhysicsSystem* sys);

    // endregion

    // region Fixed rigid body

    inline hkpRigidBody* getFixedRigidBody();
    inline const hkpRigidBody* getFixedRigidBody() const;

    // endregion

    // region Collision filter

    void updateCollisionFilterOnEntity(hkpEntity* entity,
                                       hkpUpdateCollisionFilterOnEntityMode updateMode,
                                       hkpUpdateCollectionFilterMode updateShapeCollectionFilter);

    void reenableCollisionBetweenEntityPair(hkpEntity* entityA, hkpEntity* entityB);

    void updateCollisionFilterOnPhantom(hkpPhantom* phantom,
                                        hkpUpdateCollectionFilterMode updateShapeCollectionFilter);

    void updateCollisionFilterOnWorld(hkpUpdateCollisionFilterOnWorldMode updateMode,
                                      hkpUpdateCollectionFilterMode updateShapeCollectionFilter);

    void reintegrateAndRecollideEntities(hkpEntity** entityBatch, int numEntities,
                                         ReintegrationRecollideMode mode = RR_MODE_ALL);

    // endregion

    // region Simulation

    void findInitialContactPoints(hkpEntity** entities, int numEntities);
    void findInitialContactPointsOfAllEntities();
    void calcRequiredSolverBufferSize(hkWorldMemoryAvailableWatchDog::MemUsageInfo& infoOut);
    void checkDeterminism();
    void checkDeterminismOfIslandBroadPhase(const hkpSimulationIsland* island);
    hkWorldMemoryAvailableWatchDog* getMemoryWatchDog() const;
    void setMemoryWatchDog(hkWorldMemoryAvailableWatchDog* watchDog);

    // endregion

    // region Multithreading

    enum MtAccessChecking { MT_ACCESS_CHECKING_ENABLED = 0, MT_ACCESS_CHECKING_DISABLED };

    void lock();
    void lockReadOnly();
    void unlock();
    void unlockReadOnly();
    bool checkUnmarked();
    void lockIslandForConstraintUpdate(hkpSimulationIsland* island);
    void lockForIslandSplit(hkpSimulationIsland* island);
    void unlockIslandForConstraintUpdate(hkpSimulationIsland* island);
    void unlockForIslandSplit(hkpSimulationIsland* island);
    void setMultithreadedAccessChecking(MtAccessChecking accessCheckState);
    MtAccessChecking getMultithreadedAccessChecking() const;
    void markForRead() const;
    void markForWrite();
    void unmarkForRead() const;
    void unmarkForWrite();

    // endregion

    // region Event handling

    void addActionListener(hkpActionListener* worldListener);
    void removeActionListener(hkpActionListener* worldListener);

    void addConstraintListener(hkpConstraintListener* worldListener);
    void removeConstraintListener(hkpConstraintListener* worldListener);

    void addEntityListener(hkpEntityListener* worldListener);
    void removeEntityListener(hkpEntityListener* worldListener);

    void addPhantomListener(hkpPhantomListener* worldListener);
    void removePhantomListener(hkpPhantomListener* worldListener);

    void addIslandActivationListener(hkpIslandActivationListener* worldListener);
    void removeIslandActivationListener(hkpIslandActivationListener* worldListener);

    void addWorldPostCollideListener(hkpWorldPostCollideListener* worldListener);
    void removeWorldPostCollideListener(hkpWorldPostCollideListener* worldListener);

    void addWorldPostSimulationListener(hkpWorldPostSimulationListener* worldListener);
    void removeWorldPostSimulationListener(hkpWorldPostSimulationListener* worldListener);

    void addWorldPostIntegrateListener(hkpWorldPostIntegrateListener* worldListener);
    void removeWorldPostIntegrateListener(hkpWorldPostIntegrateListener* worldListener);

    void addIslandPostCollideListener(hkpIslandPostCollideListener* islandListener);
    void removeIslandPostCollideListener(hkpIslandPostCollideListener* islandListener);

    void addIslandPostIntegrateListener(hkpIslandPostIntegrateListener* islandListener);
    void removeIslandPostIntegrateListener(hkpIslandPostIntegrateListener* islandListener);

    void addContactListener(hkpContactListener* worldListener);
    void removeContactListener(hkpContactListener* worldListener);

    const hkArray<hkpContactListener*>& getContactListeners() const;

    void addWorldDeletionListener(hkpWorldDeletionListener* worldListener);
    void removeWorldDeletionListener(hkpWorldDeletionListener* worldListener);

    void addContactImpulseLimitBreachedListener(hkpContactImpulseLimitBreachedListener* listener);
    void
    removeContactImpulseLimitBreachedListener(hkpContactImpulseLimitBreachedListener* listener);

    void addWorldExtension(hkpWorldExtension* extension);
    void removeWorldExtension(hkpWorldExtension* extension);
    hkpWorldExtension* findWorldExtension(int id) const;

    // endregion

    // region Collision detection

    inline hkpBroadPhase* getBroadPhase();
    inline const hkpBroadPhase* getBroadPhase() const;

    hkpBroadPhaseBorder* getBroadPhaseBorder() const;
    void setBroadPhaseBorder(hkpBroadPhaseBorder* bpb);

    inline const hkpProcessCollisionInput* getCollisionInput() const;
    inline hkpProcessCollisionInput* getCollisionInputRw();
    inline hkpSolverInfo* getSolverInfo();
    inline hkpCollisionDispatcher* getCollisionDispatcher() const;

    inline const hkpCollisionFilter* getCollisionFilter() const;
    void setCollisionFilter(hkpCollisionFilter* filter,
                            hkBool runUpdateCollisionFilterOnWorld = true,
                            hkpUpdateCollisionFilterOnWorldMode checkBroadPhaseMode =
                                HK_UPDATE_FILTER_ON_WORLD_FULL_CHECK,
                            hkpUpdateCollectionFilterMode updateShapeCollectionFilter =
                                HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS);

    void castRay(const hkpWorldRayCastInput& input, hkpWorldRayCastOutput& output) const;
    void castRay(const hkpWorldRayCastInput& input, hkpRayHitCollector& collector) const;
    void castRayMt(hkpWorldRayCastCommand* commandArray, int numCommands, hkJobQueue* jobQueue,
                   hkThreadPool* threadPool, hkSemaphoreBusyWait* semaphore,
                   int numCommandsPerJob = 32) const;

    /// Cast a shape.
    ///
    /// @param collA The collidable for the shape to cast.
    /// @param castCollector Collects all potential hits.
    /// @param startCollector [Optional] Collects points that are closest to the start point.
    void linearCast(const hkpCollidable* collA, const hkpLinearCastInput& input,
                    hkpCdPointCollector& castCollector,
                    hkpCdPointCollector* startCollector = nullptr) const;

    void linearCastMt(hkpWorldLinearCastCommand* commandArray, int numCommands,
                      hkJobQueue* jobQueue, hkThreadPool* threadPool,
                      hkSemaphoreBusyWait* semaphore, int numCommandsPerJob = 32) const;

    void getClosestPoints(const hkpCollidable* collA, const hkpCollisionInput& input,
                          hkpCdPointCollector& collector) const;

    void getClosestPointsMt(hkpWorldGetClosestPointsCommand* commandArray, int numCommands,
                            hkJobQueue* jobQueue, hkThreadPool* threadPool,
                            hkSemaphoreBusyWait* semaphore, int numCommandsPerJob = 32) const;

    void getPenetrations(const hkpCollidable* collA, const hkpCollisionInput& input,
                         hkpCdBodyPairCollector& collector) const;

    enum CachedAabbUpdate {
        SHIFT_BROADPHASE_UPDATE_ENTITY_AABBS,
        SHIFT_BROADPHASE_IGNORE_ENTITY_AABBS
    };
    void shiftBroadPhase(const hkVector4& shiftDistance, hkVector4& effectiveShiftDistanceOut,
                         CachedAabbUpdate updateAabbs);

    // endregion

    // region Simulation island

    inline const hkArray<hkpSimulationIsland*>& getActiveSimulationIslands() const;
    inline const hkArray<hkpSimulationIsland*>& getInactiveSimulationIslands() const;
    inline const hkpSimulationIsland* getFixedIsland() const;

    // endregion

    // region Stepping

    hkpStepResult stepDeltaTime(hkReal physicsDeltaTime);

    hkpStepResult integrate(hkReal physicsDeltaTime);
    hkpStepResult collide();
    hkpStepResult advanceTime();

    void setFrameTimeMarker(hkReal frameDeltaTime);
    bool isSimulationAtMarker() const;
    bool isSimulationAtPsi() const;

    static void registerWithJobQueue(hkJobQueue* jobQueue);
    hkpStepResult stepMultithreaded(hkJobQueue* jobQueue, hkThreadPool* threadPool,
                                    hkReal physicsDeltaTime);
    hkpStepResult initMtStep(hkJobQueue* jobQueue, hkReal physicsDeltaTime);
    hkpStepResult finishMtStep(hkJobQueue* jobQueue = nullptr, hkThreadPool* threadPool = nullptr);

    // endregion

    // region Multithreading config

    void getMultithreadConfig(hkpMultithreadConfig& config);
    void setMultithreadConfig(const hkpMultithreadConfig& config, hkJobQueue* queue);
    hkMultiThreadCheck& getMultiThreadCheck() const { return m_multiThreadCheck; }
    void checkAccessGetActiveSimulationIslands() const;

    // endregion

    // region Serialisation

    hkpPhysicsSystem* getWorldAsOneSystem() const;
    void getWorldAsSystems(hkArray<hkpPhysicsSystem*>& systemsOut) const;

    // endregion

    void removeAll();
    void attachActionToEntity(hkpAction* action, hkpEntity* entity);
    void detachActionFromEntity(hkpAction* action, hkpEntity* entity);

    // region Locking

    HK_FORCE_INLINE void lockCriticalOperations();
    HK_FORCE_INLINE void unlockCriticalOperations();
    HK_FORCE_INLINE int areCriticalOperationsLocked() const;
    HK_FORCE_INLINE int areCriticalOperationsLockedUnchecked() const;

    HK_FORCE_INLINE void unlockCriticalOperationsForPhantoms();
    HK_FORCE_INLINE void lockCriticalOperationsForPhantoms();
    HK_FORCE_INLINE int areCriticalOperationsLockedForPhantoms() const;

    HK_FORCE_INLINE void blockExecutingPendingOperations(hkBool block);
    HK_FORCE_INLINE void unlockAndAttemptToExecutePendingOperations();

    HK_FORCE_INLINE void attemptToExecutePendingOperations(bool executeBodyOperations = true);

    void queueOperation(const hkWorldOperation::BaseOperation& operation);

    hkWorldOperation::UserCallback* queueCallback(hkWorldOperation::UserCallback* callback,
                                                  hkUlong userData = 0);

    void addBodyOperation(hkpRigidBody* breakingBody, hkpBodyOperation* operation, int priority,
                          /*hkpBodyOperation::ExecutionState*/ int hint);

    void checkConstraintsViolated();

private:
    void internal_executePendingOperations();
    void internal_executePendingBodyOperations();

public:
    HK_FORCE_INLINE void allowCriticalOperations(hkBool allow);

    // endregion

    hkpSimulation* m_simulation;
    hkVector4 m_gravity;
    hkpSimulationIsland* m_fixedIsland;
    hkpRigidBody* m_fixedRigidBody;

    hkArray<hkpSimulationIsland*> m_activeSimulationIslands;
    hkArray<hkpSimulationIsland*> m_inactiveSimulationIslands;
    hkArray<hkpSimulationIsland*> m_dirtySimulationIslands;

    hkpWorldMaintenanceMgr* m_maintenanceMgr;
    hkRefPtr<hkWorldMemoryAvailableWatchDog> m_memoryWatchDog;

    hkBool m_assertOnRunningOutOfSolverMemory;

    hkEnum<hkpWorldCinfo::BroadPhaseType, hkInt8> m_broadPhaseType;
    hkpBroadPhase* m_broadPhase;

    hkpTypedBroadPhaseDispatcher* m_broadPhaseDispatcher;
    hkpPhantomBroadPhaseListener* m_phantomBroadPhaseListener;
    hkpEntityEntityBroadPhaseListener* m_entityEntityBroadPhaseListener;
    hkpBroadPhaseBorderListener* m_broadPhaseBorderListener;

    hkpMtThreadStructure* m_multithreadedSimulationJobData;
    hkpProcessCollisionInput* m_collisionInput;
    hkpCollisionFilter* m_collisionFilter;
    hkpCollisionDispatcher* m_collisionDispatcher;
    hkpConvexListFilter* m_convexListFilter;

    hkpWorldOperationQueue* m_pendingOperations;
    int m_pendingOperationsCount;
    int m_pendingBodyOperationsCount;
    int m_criticalOperationsLockCount;
    int m_criticalOperationsLockCountForPhantoms;
    hkBool m_blockExecutingPendingOperations;
    hkBool m_criticalOperationsAllowed;
    hkpDebugInfoOnPendingOperationQueues* m_pendingOperationQueues;
    int m_pendingOperationQueueCount;

    mutable hkMultiThreadCheck m_multiThreadCheck;

    hkBool m_processActionsInSingleThread;
    hkBool m_allowIntegrationOfIslandsWithoutConstraintsInASeparateJob;

    hkUint32 m_minDesiredIslandSize;

    hkCriticalSection* m_modifyConstraintCriticalSection;
    int m_isLocked;
    hkCriticalSection* m_islandDirtyListCriticalSection;
    hkCriticalSection* m_propertyMasterLock;

    hkBool m_wantSimulationIslands;

    hkReal m_snapCollisionToConvexEdgeThreshold;
    hkReal m_snapCollisionToConcaveEdgeThreshold;
    hkBool m_enableToiWeldRejection;

    hkBool m_wantDeactivation;
    hkBool m_shouldActivateOnRigidBodyTransformChange;
    hkReal m_deactivationReferenceDistance;

    hkReal m_toiCollisionResponseRotateNormal;

    int m_maxSectorsPerMidphaseCollideTask;
    int m_maxSectorsPerNarrowphaseCollideTask;
    hkBool m_processToisMultithreaded;
    int m_maxEntriesPerToiMidphaseCollideTask;
    int m_maxEntriesPerToiNarrowphaseCollideTask;
    int m_maxNumToiCollisionPairsSinglethreaded;
    hkEnum<hkpWorldCinfo::SimulationType, hkInt32> m_simulationType;
    hkReal m_numToisTillAllowedPenetrationSimplifiedToi;
    hkReal m_numToisTillAllowedPenetrationToi;
    hkReal m_numToisTillAllowedPenetrationToiHigher;
    hkReal m_numToisTillAllowedPenetrationToiForced;

    hkUint32 m_lastEntityUid;
    hkUint32 m_lastIslandUid;
    hkUint32 m_lastConstraintUid;

    friend class hkHalfstepSimulation;
    friend class hkpContinuousSimulation;
    friend class hkpMultiThreadedSimulation;
    friend class hkpSimpleConstraintContactMgr;
    friend class hkpSimulation;
    friend class hkpWorldCallbackUtil;
    friend class hkpWorldOperationUtil;

    hkArray<hkpPhantom*> m_phantoms;

    hkArray<hkpActionListener*> m_actionListeners;
    hkArray<hkpEntityListener*> m_entityListeners;
    hkArray<hkpPhantomListener*> m_phantomListeners;
    hkArray<hkpConstraintListener*> m_constraintListeners;
    hkArray<hkpWorldDeletionListener*> m_worldDeletionListeners;
    hkArray<hkpIslandActivationListener*> m_islandActivationListeners;
    hkArray<hkpWorldPostSimulationListener*> m_worldPostSimulationListeners;
    hkArray<hkpWorldPostIntegrateListener*> m_worldPostIntegrateListeners;
    hkArray<hkpWorldPostCollideListener*> m_worldPostCollideListeners;
    hkArray<hkpIslandPostIntegrateListener*> m_islandPostIntegrateListeners;
    hkArray<hkpIslandPostCollideListener*> m_islandPostCollideListeners;
    hkArray<hkpContactListener*> m_contactListeners;
    hkArray<hkpContactImpulseLimitBreachedListener*> m_contactImpulseLimitBreachedListeners;
    hkArray<hkpWorldExtension*> m_worldExtensions;
    hkpViolatedConstraintArray* m_violatedConstraintArray;

    hkpBroadPhaseBorder* m_broadPhaseBorder;

    hkdWorld* m_destructionWorld;
    hknpWorld* m_npWorld;

    hkpWorldDynamicsStepInfo m_dynamicsStepInfo;

    hkVector4 m_broadPhaseExtents[2];
    int m_broadPhaseNumMarkers;
    int m_sizeOfToiEventQueue;
    hkInt32 m_broadPhaseQuerySize;
    hkInt32 m_broadPhaseUpdateSize;
    hkEnum<hkpWorldCinfo::ContactPointGeneration, hkInt8> m_contactPointGeneration;
    hkBool m_useCompoundSpuElf;
};

inline hkpSolverInfo* hkpWorld::getSolverInfo() {
    return &m_dynamicsStepInfo.m_solverInfo;
}
