#pragma once

#include <Havok/Physics2012/Dynamics/Entity/hkpEntity.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorld.h>

class hkpRigidBodyCinfo;

class hkpRigidBody : public hkpEntity {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpRigidBody)
    HK_DECLARE_REFLECTION()

    explicit hkpRigidBody(const hkpRigidBodyCinfo& info);
    explicit hkpRigidBody(hkFinishLoadedObjectFlag flag);

    ~hkpRigidBody() override;

    /// Returns the rigid body's current state.
    void getCinfo(hkpRigidBodyCinfo& info) const;

    inline hkReal getMass() const;
    inline hkReal getMassInv() const;
    void setMass(hkReal m);
    void setMassInv(hkReal mInv);

    inline void getInertiaLocal(hkMatrix3& inertiaOut) const;
    inline void getInertiaWorld(hkMatrix3& inertiaOut) const;
    void setInertiaLocal(const hkMatrix3& inertia);
    void setInertiaInvLocal(const hkMatrix3& inertiaInv);
    inline void getInertiaInvLocal(hkMatrix3& inertiaInv) const;
    inline void getInertiaInvWorld(hkMatrix3& inertiaInvOut) const;

    void setCenterOfMassLocal(const hkVector4& centerOfMass);
    inline const hkVector4& getCenterOfMassLocal() const;
    inline const hkVector4& getCenterOfMassInWorld() const;

    inline const hkVector4& getPosition() const;
    void setPosition(const hkVector4& position);
    inline const hkQuaternion& getRotation() const;
    void setRotation(const hkQuaternion& rotation);
    void setPositionAndRotation(const hkVector4& position, const hkQuaternion& rotation);
    inline const hkTransform& getTransform() const;
    void setTransform(const hkTransform& transform);
    void setPositionAndRotationAsCriticalOperation(const hkVector4& position,
                                                   const hkQuaternion& rotation);
    inline void approxTransformAt(hkTime time, hkTransform& transformOut) const;
    inline void approxCurrentTransform(hkTransform& transformOut) const;

    inline const hkVector4& getLinearVelocity() const;
    inline void setLinearVelocity(const hkVector4& newVel);
    inline const hkVector4& getAngularVelocity() const;
    inline void setAngularVelocity(const hkVector4& newVel);
    inline void getPointVelocity(const hkVector4& p, hkVector4& vecOut) const;
    void setLinearVelocityAsCriticalOperation(const hkVector4& newVel);
    void setAngularVelocityAsCriticalOperation(const hkVector4& newVel);

    inline void applyLinearImpulse(const hkVector4& imp);
    inline void applyPointImpulse(const hkVector4& imp, const hkVector4& p);
    inline void applyAngularImpulse(const hkVector4& imp);
    void applyLinearImpulseAsCriticalOperation(const hkVector4& imp);
    void applyPointImpulseAsCriticalOperation(const hkVector4& imp, const hkVector4& p);
    void applyAngularImpulseAsCriticalOperation(const hkVector4& imp);

    inline void applyForce(hkReal deltaTime, const hkVector4& force);
    inline void applyForce(hkReal deltaTime, const hkVector4& force, const hkVector4& p);
    inline void applyTorque(hkReal deltaTime, const hkVector4& torque);

    inline hkReal getLinearDamping() const;
    inline void setLinearDamping(hkReal d);
    inline hkReal getAngularDamping() const;
    inline void setAngularDamping(hkReal d);
    inline hkReal getTimeFactor() const;
    inline void setTimeFactor(hkReal f);
    inline hkReal getGravityFactor() const;
    inline void setGravityFactor(hkReal f);

    inline hkReal getMaxLinearVelocity() const;
    inline void setMaxLinearVelocity(hkReal maxVel);
    inline hkReal getMaxAngularVelocity() const;
    inline void setMaxAngularVelocity(hkReal maxVel);

    void enableDeactivation(bool enable);
    bool isDeactivationEnabled() const;

    inline hkUint32 getCollisionFilterInfo() const;
    inline void setCollisionFilterInfo(hkUint32 info);

    inline hkpCollidableQualityType getQualityType() const;
    inline void setQualityType(hkpCollidableQualityType type);

    inline hkReal getAllowedPenetrationDepth() const;
    inline void setAllowedPenetrationDepth(hkReal val);

    void
    setMotionType(hkpMotion::MotionType newState,
                  hkpEntityActivation preferredActivationState = HK_ENTITY_ACTIVATION_DO_ACTIVATE,
                  hkpUpdateCollisionFilterOnEntityMode collisionFilterUpdateMode =
                      HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK);
    inline hkpMotion::MotionType getMotionType() const;
    hkpMotion* getStoredDynamicMotion();
    const hkpMotion* getStoredDynamicMotion() const;
    void updateCachedShapeInfo(const hkpShape* shape, hkVector4& extentOut);

    inline hkReal getFriction() const;
    inline hkReal getRollingFrictionMultiplier() const;
    inline hkReal getRestitution() const;
    void setFriction(hkReal newFriction);
    void setRollingFrictionMultiplier(hkReal multiplier);
    void setRestitution(hkReal newRestitution);

    hkWorldOperation::Result setShape(const hkpShape* shape) override;
    hkWorldOperation::Result updateShape(hkpShapeModifier* shapeModifier = nullptr) override;
    virtual hkpRigidBody* clone() const;

    inline hkpMotion* getRigidMotion() const;
    hkBool checkPerformance() const;

    static void createDynamicRigidMotion(hkpMotion::MotionType motionType,
                                         const hkVector4& position, const hkQuaternion& rotation,
                                         hkReal mass, const hkMatrix3& inertiaLocal,
                                         const hkVector4& centreOfMassLocal,
                                         hkReal maxLinearVelocity, hkReal maxAngularVelocity,
                                         hkpMaxSizeMotion* motionBufferOut);

    static void updateBroadphaseAndResetCollisionInformationOfWarpedBody(hkpEntity* entity);

protected:
    hkMotionState* getMotionState() override;
};

inline hkpRigidBody* hkpGetRigidBody(const hkpCollidable* collidable) {
    if (collidable->getType() == hkpWorldObject::BROAD_PHASE_ENTITY) {
        return static_cast<hkpRigidBody*>(hkpGetWorldObject(collidable));
    }
    return nullptr;
}

inline hkpRigidBody* hkpGetRigidBodyUnchecked(const hkpCollidable* collidable) {
    return static_cast<hkpRigidBody*>(hkpGetWorldObject(collidable));
}

inline hkReal hkpRigidBody::getMass() const {
    return getRigidMotion()->getMass();
}

inline hkReal hkpRigidBody::getMassInv() const {
    return getRigidMotion()->getMassInv();
}

inline void hkpRigidBody::getInertiaLocal(hkMatrix3& inertiaOut) const {
    getRigidMotion()->getInertiaLocal(inertiaOut);
}

inline void hkpRigidBody::getInertiaWorld(hkMatrix3& inertiaOut) const {
    getRigidMotion()->getInertiaWorld(inertiaOut);
}

inline void hkpRigidBody::getInertiaInvLocal(hkMatrix3& inertiaInv) const {
    getRigidMotion()->getInertiaInvLocal(inertiaInv);
}

inline void hkpRigidBody::getInertiaInvWorld(hkMatrix3& inertiaInvOut) const {
    getRigidMotion()->getInertiaInvWorld(inertiaInvOut);
}

inline const hkVector4& hkpRigidBody::getCenterOfMassLocal() const {
    return getRigidMotion()->getCenterOfMassLocal();
}

inline const hkVector4& hkpRigidBody::getCenterOfMassInWorld() const {
    return getRigidMotion()->getCenterOfMassInWorld();
}

inline const hkVector4& hkpRigidBody::getPosition() const {
    return getRigidMotion()->getPosition();
}

inline const hkQuaternion& hkpRigidBody::getRotation() const {
    return getRigidMotion()->getRotation();
}

inline const hkTransform& hkpRigidBody::getTransform() const {
    return getRigidMotion()->getTransform();
}

inline void hkpRigidBody::approxTransformAt(hkTime time, hkTransform& transformOut) const {
    getRigidMotion()->approxTransformAt(time, transformOut);
}

inline void hkpRigidBody::approxCurrentTransform(hkTransform& transformOut) const {
    getRigidMotion()->approxTransformAt(m_world->getCurrentTime(), transformOut);
}

inline const hkVector4& hkpRigidBody::getLinearVelocity() const {
    return getRigidMotion()->getLinearVelocity();
}

inline void hkpRigidBody::setLinearVelocity(const hkVector4& newVel) {
    getRigidMotion()->setLinearVelocity(newVel);
}

inline const hkVector4& hkpRigidBody::getAngularVelocity() const {
    return getRigidMotion()->getAngularVelocity();
}

inline void hkpRigidBody::setAngularVelocity(const hkVector4& newVel) {
    getRigidMotion()->setAngularVelocity(newVel);
}

inline void hkpRigidBody::getPointVelocity(const hkVector4& p, hkVector4& vecOut) const {
    getRigidMotion()->getPointVelocity(p, vecOut);
}

inline void hkpRigidBody::applyLinearImpulse(const hkVector4& imp) {
    activate();
    getRigidMotion()->applyLinearImpulse(imp);
}

inline void hkpRigidBody::applyPointImpulse(const hkVector4& imp, const hkVector4& p) {
    activate();
    getRigidMotion()->applyPointImpulse(imp, p);
}

inline void hkpRigidBody::applyAngularImpulse(const hkVector4& imp) {
    activate();
    getRigidMotion()->applyAngularImpulse(imp);
}

inline void hkpRigidBody::applyForce(const hkReal deltaTime, const hkVector4& force) {
    activate();
    getRigidMotion()->applyForce(deltaTime, force);
}

inline void hkpRigidBody::applyForce(const hkReal deltaTime, const hkVector4& force,
                                     const hkVector4& p) {
    activate();
    getRigidMotion()->applyForce(deltaTime, force, p);
}

inline void hkpRigidBody::applyTorque(const hkReal deltaTime, const hkVector4& torque) {
    activate();
    getRigidMotion()->applyTorque(deltaTime, torque);
}

inline hkReal hkpRigidBody::getLinearDamping() const {
    return getRigidMotion()->getLinearDamping();
}

inline void hkpRigidBody::setLinearDamping(hkReal d) {
    getRigidMotion()->setLinearDamping(d);
}

inline hkReal hkpRigidBody::getAngularDamping() const {
    return getRigidMotion()->getAngularDamping();
}

inline void hkpRigidBody::setAngularDamping(hkReal d) {
    getRigidMotion()->setAngularDamping(d);
}

inline hkReal hkpRigidBody::getTimeFactor() const {
    return getRigidMotion()->getTimeFactor();
}

inline void hkpRigidBody::setTimeFactor(hkReal f) {
    getRigidMotion()->setTimeFactor(f);
}

inline hkReal hkpRigidBody::getGravityFactor() const {
    return getRigidMotion()->getGravityFactor();
}

inline void hkpRigidBody::setGravityFactor(hkReal f) {
    getRigidMotion()->setGravityFactor(f);
}

inline hkReal hkpRigidBody::getMaxLinearVelocity() const {
    return getRigidMotion()->getMotionState()->m_maxLinearVelocity;
}

inline void hkpRigidBody::setMaxLinearVelocity(hkReal maxVel) {
    getRigidMotion()->getMotionState()->m_maxLinearVelocity = maxVel;
}

inline hkReal hkpRigidBody::getMaxAngularVelocity() const {
    return getRigidMotion()->getMotionState()->m_maxAngularVelocity;
}

inline void hkpRigidBody::setMaxAngularVelocity(hkReal maxVel) {
    getRigidMotion()->getMotionState()->m_maxAngularVelocity = maxVel;
}

inline hkUint32 hkpRigidBody::getCollisionFilterInfo() const {
    return getCollidable()->getCollisionFilterInfo();
}

inline void hkpRigidBody::setCollisionFilterInfo(hkUint32 info) {
    getCollidableRw()->setCollisionFilterInfo(info);
}

inline hkpCollidableQualityType hkpRigidBody::getQualityType() const {
    return getCollidable()->getQualityType();
}

inline void hkpRigidBody::setQualityType(hkpCollidableQualityType type) {
    getCollidableRw()->setQualityType(type);
}

inline hkReal hkpRigidBody::getAllowedPenetrationDepth() const {
    return getCollidable()->m_allowedPenetrationDepth;
}

inline void hkpRigidBody::setAllowedPenetrationDepth(hkReal val) {
    getCollidableRw()->m_allowedPenetrationDepth = val;
}

inline hkpMotion::MotionType hkpRigidBody::getMotionType() const {
    return getRigidMotion()->getType();
}

inline hkReal hkpRigidBody::getFriction() const {
    return m_material.getFriction();
}

inline hkReal hkpRigidBody::getRollingFrictionMultiplier() const {
    return m_material.getRollingFrictionMultiplier();
}

inline hkReal hkpRigidBody::getRestitution() const {
    return m_material.getRestitution();
}

inline hkpMotion* hkpRigidBody::getRigidMotion() const {
    return const_cast<hkpMaxSizeMotion*>(&m_motion);
}
