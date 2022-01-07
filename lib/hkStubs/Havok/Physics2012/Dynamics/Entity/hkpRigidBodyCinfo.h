#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidableQualityType.h>
#include <Havok/Physics2012/Dynamics/Common/hkpMaterial.h>
#include <Havok/Physics2012/Dynamics/Motion/hkpMotion.h>

class hkLocalFrame;
class hkpShape;

class hkpRigidBodyCinfo {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpRigidBodyCinfo)

    enum SolverDeactivation {
        SOLVER_DEACTIVATION_INVALID,
        SOLVER_DEACTIVATION_OFF,
        SOLVER_DEACTIVATION_LOW,
        SOLVER_DEACTIVATION_MEDIUM,
        SOLVER_DEACTIVATION_HIGH,
        SOLVER_DEACTIVATION_MAX
    };

    hkpRigidBodyCinfo();

    void setMassProperties(const struct hkMassProperties& mp);
    void setTransform(const hkTransform& transform);

    hkUint32 m_collisionFilterInfo;
    const hkpShape* m_shape;
    hkVector4 m_position;
    hkQuaternion m_rotation;
    hkVector4 m_linearVelocity;
    hkVector4 m_angularVelocity;
    hkMatrix3 m_inertiaTensor;
    hkVector4 m_centerOfMass;
    hkReal m_mass;
    hkReal m_linearDamping;
    hkReal m_angularDamping;
    hkReal m_gravityFactor;
    hkReal m_friction;
    hkReal m_rollingFrictionMultiplier;
    hkReal m_restitution;
    hkReal m_maxLinearVelocity;
    hkReal m_maxAngularVelocity;
    hkEnum<hkpMotion::MotionType, hkInt8> m_motionType;
    hkBool m_enableDeactivation;
    hkEnum<SolverDeactivation, hkInt8> m_solverDeactivation;
    hkReal m_allowedPenetrationDepth;
    hkReal m_timeFactor;
    hkLocalFrame* m_localFrame;
    hkEnum<hkpMaterial::ResponseType, hkInt8> m_collisionResponse;
    hkUint16 m_contactPointCallbackDelay;
    hkEnum<hkpCollidableQualityType, hkInt8> m_qualityType;
    hkInt8 m_autoRemoveLevel;
    hkUint8 m_responseModifierFlags;
    hkInt8 m_numShapeKeysInContactPointProperties;
    hkBool m_forceCollideOntoPpu;
};
