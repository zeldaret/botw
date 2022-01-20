#pragma once

#include <Havok/Common/Base/hkBase.h>

/// This is a simplified rigid body as it is used by the constraint solver.
/// Note: This class has different purposes, whether it is used for setting up the constraint solver
/// input (hkConstraintDate::buildJacobian()), or when it is used as a solver output.
class hkpVelocityAccumulator {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpVelocityAccumulator)

    enum hkpAccumulatorType {
        HK_RIGID_BODY,
        HK_KEYFRAMED_RIGID_BODY,
        HK_NO_GRAVITY_RIGID_BODY,
        HK_END
    };

    enum hkpAccumulatorContext {
        ACCUMULATOR_CONTEXT_BUILD_JACOBIANS,
        ACCUMULATOR_CONTEXT_SOLVER,
    };

    hkEnum<hkpAccumulatorType, hkUint8> m_type;
    hkEnum<hkpAccumulatorContext, hkUint8> m_context;
    hkUint32 m_deactivationClass;
    hkReal m_gravityFactor;
    hkVector4 m_linearVel;
    hkVector4 m_angularVel;
    hkVector4 m_invMasses;
    hkVector4 m_scratch0;
    hkVector4 m_scratch1;
    hkVector4 m_scratch2;
    hkVector4 m_scratch3;
};
