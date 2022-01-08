#pragma once

#include <Havok/Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Filter/hkpCollisionFilter.h>
#include <Havok/Physics2012/Collide/Filter/hkpConvexListFilter.h>
#include <Havok/Physics2012/Dynamics/World/Memory/hkpWorldMemoryAvailableWatchDog.h>

class hkpWorldCinfo : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpWorldCinfo)

    enum SolverType {
        SOLVER_TYPE_INVALID,
        SOLVER_TYPE_2ITERS_SOFT,
        SOLVER_TYPE_2ITERS_MEDIUM,
        SOLVER_TYPE_2ITERS_HARD,
        SOLVER_TYPE_4ITERS_SOFT,
        SOLVER_TYPE_4ITERS_MEDIUM,
        SOLVER_TYPE_4ITERS_HARD,
        SOLVER_TYPE_8ITERS_SOFT,
        SOLVER_TYPE_8ITERS_MEDIUM,
        SOLVER_TYPE_8ITERS_HARD,
        SOLVER_TYPE_MAX_ID
    };

    enum SimulationType {
        SIMULATION_TYPE_INVALID,
        SIMULATION_TYPE_DISCRETE,
        SIMULATION_TYPE_CONTINUOUS,
        SIMULATION_TYPE_MULTITHREADED,
    };

    enum ContactPointGeneration {
        CONTACT_POINT_ACCEPT_ALWAYS,
        CONTACT_POINT_REJECT_DUBIOUS,
        CONTACT_POINT_REJECT_MANY,
    };

    enum BroadPhaseType {
        BROADPHASE_TYPE_SAP,
        BROADPHASE_TYPE_TREE,
        BROADPHASE_TYPE_HYBRID,
    };

    enum BroadPhaseBorderBehaviour {
        BROADPHASE_BORDER_ASSERT,
        BROADPHASE_BORDER_FIX_ENTITY,
        BROADPHASE_BORDER_REMOVE_ENTITY,
        BROADPHASE_BORDER_DO_NOTHING,
    };

    hkpWorldCinfo();
    explicit hkpWorldCinfo(hkFinishLoadedObjectFlag flag);
    ~hkpWorldCinfo() override = default;

    void setupSolverInfo(SolverType st);
    void setBroadPhaseWorldSize(hkReal size);

    hkVector4 m_gravity;
    hkInt32 m_broadPhaseQuerySize;
    hkReal m_contactRestingVelocity;
    hkEnum<BroadPhaseType, hkInt8> m_broadPhaseType;
    hkEnum<BroadPhaseBorderBehaviour, hkInt8> m_broadPhaseBorderBehaviour;
    hkBool m_mtPostponeAndSortBroadPhaseBorderCallbacks;
    hkAabb m_broadPhaseWorldAabb;
    hkReal m_collisionTolerance;
    hkRefPtr<hkpCollisionFilter> m_collisionFilter;
    hkRefPtr<hkpConvexListFilter> m_convexListFilter;
    hkReal m_expectedMaxLinearVelocity;
    int m_sizeOfToiEventQueue;
    hkReal m_expectedMinPsiDeltaTime;
    hkRefPtr<hkWorldMemoryAvailableWatchDog> m_memoryWatchDog;

    hkInt32 m_broadPhaseNumMarkers;
    hkEnum<ContactPointGeneration, hkInt8> m_contactPointGeneration;
    hkBool m_allowToSkipConfirmedCallbacks;

    hkReal m_solverTau;
    hkReal m_solverDamp;
    hkInt32 m_solverIterations;
    hkInt32 m_solverMicrosteps;
    hkReal m_maxConstraintViolation;
    hkBool m_forceCoherentConstraintOrderingInSolver;

    hkReal m_snapCollisionToConvexEdgeThreshold;
    hkReal m_snapCollisionToConcaveEdgeThreshold;
    hkBool m_enableToiWeldRejection;
    hkBool m_enableDeprecatedWelding;
    hkReal m_iterativeLinearCastEarlyOutDistance;
    hkInt32 m_iterativeLinearCastMaxIterations;
    hkUint8 m_deactivationNumInactiveFramesSelectFlag0;
    hkUint8 m_deactivationNumInactiveFramesSelectFlag1;
    hkUint8 m_deactivationIntegrateCounter;
    hkBool m_shouldActivateOnRigidBodyTransformChange;
    hkReal m_deactivationReferenceDistance;
    hkReal m_toiCollisionResponseRotateNormal;

    hkBool m_useCompoundSpuElf;
    int m_maxSectorsPerMidphaseCollideTask;
    int m_maxSectorsPerNarrowphaseCollideTask;
    hkBool m_processToisMultithreaded;
    int m_maxEntriesPerToiMidphaseCollideTask;
    int m_maxEntriesPerToiNarrowphaseCollideTask;
    int m_maxNumToiCollisionPairsSinglethreaded;
    hkReal m_numToisTillAllowedPenetrationSimplifiedToi;
    hkReal m_numToisTillAllowedPenetrationToi;
    hkReal m_numToisTillAllowedPenetrationToiHigher;
    hkReal m_numToisTillAllowedPenetrationToiForced;

    hkBool m_enableDeactivation;
    hkEnum<SimulationType, hkInt8> m_simulationType;
    hkBool m_enableSimulationIslands;
    hkUint32 m_minDesiredIslandSize;
    hkBool m_processActionsInSingleThread;
    hkBool m_allowIntegrationOfIslandsWithoutConstraintsInASeparateJob;
    hkReal m_frameMarkerPsiSnap;
    hkBool m_fireCollisionCallbacks;
};
