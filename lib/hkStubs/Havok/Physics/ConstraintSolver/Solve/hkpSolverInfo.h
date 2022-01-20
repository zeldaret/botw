#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkpSolverInfo {
    HK_DECLARE_CLASS_ALLOCATOR(hkpSolverInfo)

    enum DeactivationClass {
        DEACTIVATION_CLASS_INVALID,
        DEACTIVATION_CLASS_OFF,
        DEACTIVATION_CLASS_LOW,
        DEACTIVATION_CLASS_MEDIUM,
        DEACTIVATION_CLASS_HIGH,
        DEACTIVATION_CLASS_AGGRESSIVE,
        DEACTIVATION_CLASSES_END
    };

    struct DeactivationInfo {
        HK_DECLARE_CLASS_ALLOCATOR(DeactivationInfo)

        hkReal m_linearVelocityThresholdInv;
        hkReal m_angularVelocityThresholdInv;
        hkReal m_slowObjectVelocityMultiplier;
        hkReal m_relativeSleepVelocityThreshold;
        hkReal m_maxDistSqrd[2];
        hkReal m_maxRotSqrd[2];
    };

    alignas(16) hkReal m_padding;
    hkReal m_tau;
    hkReal m_damping;
    hkReal m_frictionTau;

    hkVector4 m_globalAccelerationPerSubStep;
    hkVector4 m_globalAccelerationPerStep;

    hkVector4 m_integrateVelocityFactor;
    hkVector4 m_invIntegrateVelocityFactor;

    hkReal m_dampDivTau;
    hkReal m_tauDivDamp;
    hkReal m_dampDivFrictionTau;
    hkReal m_frictionTauDivDamp;
    hkReal m_contactRestingVelocity;
    DeactivationInfo m_deactivationInfo[DEACTIVATION_CLASSES_END];

    hkReal m_deltaTime;
    hkReal m_invDeltaTime;
    int m_numSteps;
    int m_numMicroSteps;
    hkReal m_invNumMicroSteps;
    hkReal m_invNumSteps;

    hkBool m_forceCoherentConstraintOrderingInSolver;

    hkUint8 m_deactivationNumInactiveFramesSelectFlag[2];
    hkUint8 m_deactivationIntegrateCounter;

    hkReal m_maxConstraintViolationSqrd;
};
