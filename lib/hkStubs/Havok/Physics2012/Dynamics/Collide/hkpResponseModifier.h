#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpConstraintInstance;
class hkpConstraintOwner;
class hkpDynamicsContactMgr;
class hkpRigidBody;

class hkpResponseModifier {
public:
    enum Flags {
        MASS_SCALING = 1,
        CENTER_OF_MASS_DISPLACEMENT = 2,
        SURFACE_VELOCITY = 4,
        IMPULSE_SCALING = 8,
        VISCOUS_SURFACE = 16,

        ADDITIONAL_SIZE_MODIFIERS = MASS_SCALING | CENTER_OF_MASS_DISPLACEMENT | SURFACE_VELOCITY,
    };

    static void setInvMassScalingForContact(hkpDynamicsContactMgr* manager, hkpRigidBody* bodyA,
                                            hkpRigidBody* bodyB,
                                            hkpConstraintOwner& constraintOwner,
                                            const hkVector4& factorA, const hkVector4& factorB);

    static void setInvMassScalingForContact(hkpDynamicsContactMgr* manager, hkpRigidBody* body,
                                            hkpConstraintOwner& constraintOwner,
                                            const hkVector4& factor);

    static void setCenterOfMassDisplacementForContact(hkpDynamicsContactMgr* manager,
                                                      hkpRigidBody* bodyA, hkpRigidBody* bodyB,
                                                      hkpConstraintOwner& constraintOwner,
                                                      const hkVector4& displacementA,
                                                      const hkVector4& displacementB);

    static void setImpulseScalingForContact(hkpDynamicsContactMgr* manager, hkpRigidBody* bodyA,
                                            hkpRigidBody* bodyB,
                                            hkpConstraintOwner& constraintOwner,
                                            hkReal usedImpulseFraction, hkReal maxAcceleration);

    static void setSurfaceVelocity(hkpDynamicsContactMgr* manager, hkpRigidBody* body,
                                   hkpConstraintOwner& constraintOwner, const hkVector4& velWorld);

    static void clearSurfaceVelocity(hkpDynamicsContactMgr* manager,
                                     hkpConstraintOwner& constraintOwner, hkpRigidBody* body);

    static void setLowSurfaceViscosity(hkpDynamicsContactMgr* manager,
                                       hkpConstraintOwner& constraintOwner);

    static void disableConstraint(hkpConstraintInstance* instance,
                                  hkpConstraintOwner& constraintOwner);

    static void enableConstraint(hkpConstraintInstance* instance,
                                 hkpConstraintOwner& constraintOwner);

    HK_FORCE_INLINE static hkUint16 getAdditionalSchemaSize(hkUint8 flags);

    static const hkUint16 tableOfAdditionalSchemaSizes[];
};

inline hkUint16 hkpResponseModifier::getAdditionalSchemaSize(hkUint8 flags) {
    return tableOfAdditionalSchemaSizes[flags & ADDITIONAL_SIZE_MODIFIERS];
}
