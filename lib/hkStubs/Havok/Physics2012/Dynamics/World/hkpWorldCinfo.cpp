#include <Havok/Physics2012/Dynamics/World/hkpWorldCinfo.h>

hkpWorldCinfo::hkpWorldCinfo() {
    m_gravity = {0, -9.8, 0};
    m_enableSimulationIslands = true;
    m_broadPhaseQuerySize = 1024;
    m_mtPostponeAndSortBroadPhaseBorderCallbacks = false;
    m_broadPhaseWorldAabb = {{-500, -500, -500}, {500, 500, 500}};
    m_collisionFilter = nullptr;
    m_convexListFilter = nullptr;
    m_broadPhaseNumMarkers = 0;
    m_sizeOfToiEventQueue = 250;
    m_solverTau = 0.6;
    m_solverDamp = 1.0;
    m_contactRestingVelocity = 1.0;
    m_solverIterations = 4;
    m_solverMicrosteps = 1;
    m_maxConstraintViolation = 1.8446726e+19;
    m_forceCoherentConstraintOrderingInSolver = false;
    m_snapCollisionToConvexEdgeThreshold = 0.524;
    m_snapCollisionToConcaveEdgeThreshold = 0.698;
    m_enableToiWeldRejection = false;
    m_collisionTolerance = 0.1;
    m_broadPhaseType = BROADPHASE_TYPE_SAP;
    m_broadPhaseBorderBehaviour = BROADPHASE_BORDER_ASSERT;
    m_toiCollisionResponseRotateNormal = 0.2;
    m_useCompoundSpuElf = false;
    m_processToisMultithreaded = true;
    m_maxSectorsPerMidphaseCollideTask = 2;
    m_maxSectorsPerNarrowphaseCollideTask = 4;
    m_maxEntriesPerToiMidphaseCollideTask = 4;
    m_maxEntriesPerToiNarrowphaseCollideTask = 12;
    m_maxNumToiCollisionPairsSinglethreaded = 0;
    m_numToisTillAllowedPenetrationSimplifiedToi = 3.0;
    m_numToisTillAllowedPenetrationToi = 3.0;
    m_numToisTillAllowedPenetrationToiHigher = 4.0;
    m_numToisTillAllowedPenetrationToiForced = 20.0;
    m_deactivationReferenceDistance = 0.02;
    m_expectedMaxLinearVelocity = 200;
    m_expectedMinPsiDeltaTime = 1.0f / 30.0f;
    m_iterativeLinearCastEarlyOutDistance = 0.01;
    m_enableDeprecatedWelding = false;
    m_iterativeLinearCastMaxIterations = 20;
    m_enableDeactivation = true;
    m_shouldActivateOnRigidBodyTransformChange = true;
    m_minDesiredIslandSize = 64;
    m_deactivationNumInactiveFramesSelectFlag0 = 0;
    m_deactivationNumInactiveFramesSelectFlag1 = 0;
    m_deactivationIntegrateCounter = 0;
    m_contactPointGeneration = CONTACT_POINT_REJECT_MANY;
    m_allowToSkipConfirmedCallbacks = false;
    m_simulationType = SIMULATION_TYPE_CONTINUOUS;
    m_frameMarkerPsiSnap = 0.0001;
    m_memoryWatchDog = nullptr;
    m_processActionsInSingleThread = true;
    m_allowIntegrationOfIslandsWithoutConstraintsInASeparateJob = false;
    m_fireCollisionCallbacks = false;
}

void hkpWorldCinfo::setBroadPhaseWorldSize(hkReal size) {
    m_broadPhaseWorldAabb.m_min.setAll(-0.5f * size);
    m_broadPhaseWorldAabb.m_max.setAll(0.5f * size);
}

void hkpWorldCinfo::setupSolverInfo(hkpWorldCinfo::SolverType st) {
    switch (st) {
    case SOLVER_TYPE_2ITERS_SOFT:
        m_solverTau = 0.3;
        m_solverDamp = 0.9;
        m_solverIterations = 2;
        break;
    case SOLVER_TYPE_2ITERS_MEDIUM:
        m_solverTau = 0.6;
        m_solverDamp = 1.0;
        m_solverIterations = 2;
        break;
    case SOLVER_TYPE_2ITERS_HARD:
        m_solverTau = 0.9;
        m_solverDamp = 1.1;
        m_solverIterations = 2;
        break;

    case SOLVER_TYPE_4ITERS_SOFT:
        m_solverTau = 0.3;
        m_solverDamp = 0.9;
        m_solverIterations = 4;
        break;
    case SOLVER_TYPE_4ITERS_MEDIUM:
        m_solverTau = 0.6;
        m_solverDamp = 1.0;
        m_solverIterations = 4;
        break;
    case SOLVER_TYPE_4ITERS_HARD:
        m_solverTau = 0.9;
        m_solverDamp = 1.1;
        m_solverIterations = 4;
        break;

    case SOLVER_TYPE_8ITERS_SOFT:
        m_solverTau = 0.3;
        m_solverDamp = 0.9;
        m_solverIterations = 8;
        break;
    case SOLVER_TYPE_8ITERS_MEDIUM:
        m_solverTau = 0.6;
        m_solverDamp = 1.0;
        m_solverIterations = 8;
        break;
    case SOLVER_TYPE_8ITERS_HARD:
        m_solverTau = 0.9;
        m_solverDamp = 1.1;
        m_solverIterations = 8;
        break;

    case SOLVER_TYPE_INVALID:
    case SOLVER_TYPE_MAX_ID:
        break;
    }
}

hkpWorldCinfo::hkpWorldCinfo(hkFinishLoadedObjectFlag flag)
    : hkReferencedObject(flag), m_collisionFilter(flag), m_convexListFilter(flag),
      m_memoryWatchDog(flag) {
    if (!flag.m_finishing)
        return;

    if (m_contactRestingVelocity == 0.0)
        m_contactRestingVelocity = 1.0;

    if (m_maxEntriesPerToiMidphaseCollideTask == -1)
        m_maxEntriesPerToiMidphaseCollideTask = 4;

    if (m_maxEntriesPerToiNarrowphaseCollideTask == -1)
        m_maxEntriesPerToiNarrowphaseCollideTask = 12;
}
