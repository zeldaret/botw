#pragma once

#include <container/seadPtrArray.h>
#include <gfx/seadColor.h>
#include <heap/seadDisposer.h>
#include <math/seadBoundBox.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyAccessor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyContactEvent.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

enum hkpCollidableQualityType : int;
class hkQuaternionf;
class hkVector4f;
class hkpCollidable;
class hkpRigidBody;
class hkpShape;
class hkpMaxSizeMotion;
class hkpMotion;

namespace ksys::phys {

class CollisionInfo;
class ContactPointInfo;
class MotionAccessor;
struct RigidBodyInstanceParam;
class RigidBodyMotionEntity;
class RigidBodyMotionSensor;
class SystemGroupHandler;
class UserTag;

class RigidBase {
public:
    virtual ~RigidBase() = default;
};

struct RigidBodyCollisionMasks {
    /// See MaterialMaskData.
    u32 material_mask;
    /// EntityCollisionFilterInfo or ReceiverMask.
    u32 collision_filter_info;
    /// Contact layers we do not collide with.
    /// One bit per ContactLayer -- layers are relative to the layer base value.
    u32 ignored_layers;
};

class RigidBody : public sead::IDisposer, public RigidBase {
    SEAD_RTTI_BASE(RigidBody)
public:
    using CollisionMasks = RigidBodyCollisionMasks;

    enum class Type {
        FromShape = 0,
        Ragdoll = 1,
        _2 = 2,
        TerrainHeightField = 3,
        StaticCompoundBody = 4,
        CharacterController = 5,
        TeraMesh = 6,
    };

    enum class Flag {
        IsSensor = 1 << 0,
        UpdateRequested = 1 << 1,
        _4 = 1 << 2,
        IsAddedToWorld = 1 << 3,
        _10 = 1 << 4,
        _20 = 1 << 5,
        _40 = 1 << 6,
        /// Indicates whether the Havok collidable has been configured to use a higher quality type.
        HighQualityCollidable = 1 << 7,
        UseSystemTimeFactor = 1 << 8,
        _200 = 1 << 9,
        _400 = 1 << 10,
        _800 = 1 << 11,
        _1000 = 1 << 12,
        _2000 = 1 << 13,
        _4000 = 1 << 14,
        _8000 = 1 << 15,
        _10000 = 1 << 16,
        FixedWithImpulsePreserved = 1 << 17,
        Fixed = 1 << 18,
        Frozen = 1 << 19,
        _100000 = 1 << 20,
        _200000 = 1 << 21,
        _400000 = 1 << 22,
        _800000 = 1 << 23,
        _1000000 = 1 << 24,
        _2000000 = 1 << 25,
        _4000000 = 1 << 26,
        _8000000 = 1 << 27,
        NoCharStandingOn = 1 << 28,
        _20000000 = 1 << 29,
        _40000000 = 1 << 30,
        _80000000 = 1 << 31,
    };

    enum class MotionFlag {
        /// Whether somebody requested that the rigid body be added to the world.
        BodyAddRequested = 1 << 0,
        /// Whether somebody requested that the rigid body be removed from the world.
        BodyRemovalRequested = 1 << 1,
        Dynamic = 1 << 2,
        Keyframed = 1 << 3,
        Fixed = 1 << 4,
        DirtyTransform = 1 << 5,
        DirtyLinearVelocity = 1 << 6,
        DirtyAngularVelocity = 1 << 7,
        DirtyMaxVelOrTimeFactor = 1 << 8,
        DirtyMiscState = 1 << 9,
        DirtyMass = 1 << 10,
        DirtyCenterOfMassLocal = 1 << 11,
        DirtyInertiaLocal = 1 << 12,
        DirtyDampingOrGravityFactor = 1 << 13,
        DirtyShape = 1 << 14,
        _8000 = 1 << 15,
        _10000 = 1 << 16,
        _20000 = 1 << 17,
        _40000 = 1 << 18,
        _80000 = 1 << 19,
    };

    class ScopedLock {
    public:
        explicit ScopedLock(RigidBody* body, bool also_lock_world)
            : mBody(body), mAlsoLockWorld(also_lock_world) {
            mBody->lock(also_lock_world);
        }
        ~ScopedLock() { mBody->unlock(mAlsoLockWorld); }
        ScopedLock(const ScopedLock&) = delete;
        auto operator=(const ScopedLock&) = delete;

    private:
        RigidBody* mBody;
        bool mAlsoLockWorld;
    };

    RigidBody(Type type, ContactLayerType layer_type, hkpRigidBody* hk_body,
              const sead::SafeString& name, sead::Heap* heap, bool set_flag_10);
    ~RigidBody() override;

    virtual float getVolume();

    bool initMotionAccessorForDynamicMotion(sead::Heap* heap);
    bool initMotionAccessor(const RigidBodyInstanceParam& param, sead::Heap* heap,
                            bool init_motion);
    /// Create a hkpMotion in the specified motion storage and initialise it.
    bool createMotion(hkpMaxSizeMotion* motion, MotionType motion_type,
                      const RigidBodyInstanceParam& param);

    sead::SafeString getHkBodyName() const;
    hkpCollidable* getCollidable() const;

    void addToWorld();
    bool isActive() const;
    bool isAddedToWorld() const;
    bool isAddingBodyToWorld() const;
    bool isRemovingBodyFromWorld() const;
    void removeFromWorld();
    /// Returns true if the system has finished removing the body from the world and
    /// resetting body/accessor links, false otherwise.
    bool removeFromWorldAndResetLinks();

    /// Get the motion accessor if it is a RigidBodyMotionEntity. Returns nullptr otherwise.
    RigidBodyMotionEntity* getEntityMotionAccessor() const;
    /// Get the motion accessor if it is a RigidBodyMotionEntity. Returns nullptr otherwise.
    /// For internal use by the physics system.
    RigidBodyMotionEntity* getEntityMotionAccessorForSensor() const;

    /// Get the motion accessor if it is a RigidBodyMotionSensor. Returns nullptr otherwise.
    RigidBodyMotionSensor* getSensorMotionAccessor() const;
    /// Get the linked rigid body from the sensor motion accessor (or nullptr if there is none).
    RigidBody* getLinkedRigidBody() const;
    /// Reset the linked rigid body if we have a sensor motion accessor.
    void resetLinkedRigidBody() const;
    /// Set the linked rigid body. This can only be done for sensor rigid bodies.
    bool setLinkedRigidBody(RigidBody* body);
    bool isSensorMotionFlag40000Set() const;

    // 0x0000007100f8d840
    void removeFromWorldImmediately(void* arg = nullptr);

    MotionType getMotionType() const;

    void replaceMotionObject();
    // 0x0000007100f8e110
    void x_10();
    // 0x0000007100f8e3fc
    void x_11();

    CollisionInfo* getCollisionInfo() const { return mCollisionInfo; }
    void setCollisionInfo(CollisionInfo* info);

    ContactPointInfo* getContactPointInfo() const { return mContactPointInfo; }
    void setContactPointInfo(ContactPointInfo* info);

    void freeze(bool should_freeze, bool preserve_velocities, bool preserve_max_impulse);
    void setFixedAndPreserveImpulse(bool fixed, bool mark_linear_vel_as_dirty);
    void setFixed(bool fixed, bool preserve_velocities);
    void resetFrozenState();

    // 0x0000007100f8ee50 - FIXME: figure out what type is
    void x_17(u8 type);

    void updateCollidableQualityType(bool high_quality);

    void enableContactLayer(ContactLayer layer);
    void disableContactLayer(ContactLayer layer);
    void setContactMask(u32);
    void setContactAll();
    void setContactNone();
    sead::BitFlag32 getContactMask() const { return mContactMask; }
    sead::BitFlag32 getIgnoredLayers() const { return ~getContactMask(); }

    void enableGroundCollision(bool enabled);
    bool isGroundCollisionEnabled() const;

    void enableWaterCollision(bool enabled);
    bool isWaterCollisionEnabled() const;

    // region Collision filter info, receiver, group handler

    ContactLayer getContactLayer() const;
    ContactLayer getContactLayer(EntityCollisionMask info) const;
    /// Set a new contact layer. Its type must match the layer type of this rigid body.
    /// (Otherwise, this function does nothing.)
    void setContactLayer(ContactLayer layer);

    u32 getCollisionFilterInfo() const;
    void setCollisionFilterInfo(u32 info);

    auto getEntityCollisionFilterInfo() const {
        return EntityCollisionMask(getCollisionFilterInfo());
    }

    /// Only works for sensor rigid bodies that do not use a custom receiver.
    void setSensorReceiverIgnoredLayer(ContactLayer layer);
    /// Only works for sensor rigid bodies that do not use a custom receiver.
    void clearSensorReceiverIgnoredLayer();

    void setContactLayerAndHandler(ContactLayer layer, SystemGroupHandler* handler);
    void setContactLayerAndGroundHit(ContactLayer layer, GroundHit ground_hit);
    void setContactLayerAndGroundHitAndHandler(ContactLayer layer, GroundHit ground_hit,
                                               SystemGroupHandler* handler);

    void setSystemGroupHandler(SystemGroupHandler* handler);

    void setSensorCustomReceiver(const SensorCollisionMask& mask);
    void setSensorCustomReceiver(const SensorCollisionMask& mask,
                                 const SystemGroupHandler* handler);

    // endregion

    // region Ground hit

    /// Replace the current collision filter info with a ground hit mask.
    /// @param layer Contact layer (must be an entity layer; this function does nothing otherwise)
    /// @param mask  The new ground hit mask
    void setGroundHitMask(ContactLayer layer, u32 mask);

    /// Add a ground hit type to an existing ground hit mask.
    /// If this rigid body does not already have a ground hit mask or isn't an entity,
    /// then this function does nothing.
    void addGroundTypeToGroundHitMask(GroundHit ground_hit);

    /// Get the ground hit type for this rigid body.
    /// Only valid for entity rigid bodies that do *not* have a ground hit mask
    /// but a normal entity mask. Returns 0 if this is a sensor, HitAll if in ground hit mask mode.
    GroundHit getGroundHitType() const;

    /// Set a ground hit type. This can only be done for entity rigid bodies.
    void setGroundHitType(GroundHit ground_hit);

    // endregion

    void setColor(const sead::Color4f& color, const void* a, bool b);

    void setPosition(const sead::Vector3f& position, bool propagate_to_linked_motions);
    void getPosition(sead::Vector3f* position) const;
    sead::Vector3f getPosition() const;
    virtual void onImpulse(RigidBody* body_b, float impulse) const;
    void getAabbInLocal(sead::BoundBox3f* aabb) const;
    void getAabbInWorld(sead::BoundBox3f* aabb) const;

    void getRotation(sead::Quatf* rotation) const;
    sead::Quatf getRotation() const;

    void getPositionAndRotation(sead::Vector3f* position, sead::Quatf* rotation) const;

    void getTransform(sead::Matrix34f* mtx) const;
    sead::Matrix34f getTransform() const;
    void setTransform(const sead::Matrix34f& mtx, bool propagate_to_linked_motions);
    bool isTransformDirty() const;

    void updateShape();
    void setScale(float scale);

    void changeMotionType(MotionType motion_type);
    // 0x0000007100f9045c - calls a bunch of Havok world functions
    void doChangeMotionType(MotionType x, MotionType y);
    // 0x0000007100f908c8
    void x_40();
    void updateMotionTypeRelatedFlags();
    void triggerScheduledMotionTypeChange();

    // region Velocity

    bool setLinearVelocity(const sead::Vector3f& velocity, float epsilon = sead::Mathf::epsilon());
    void getLinearVelocity(sead::Vector3f* velocity) const;
    sead::Vector3f getLinearVelocity() const;

    bool setAngularVelocity(const sead::Vector3f& velocity, float epsilon = sead::Mathf::epsilon());
    void getAngularVelocity(sead::Vector3f* velocity) const;
    sead::Vector3f getAngularVelocity() const;

    void getPointVelocity(sead::Vector3f* velocity, const sead::Vector3f& point) const;

    /// Move to the specified position and rotation by changing the linear and angular velocities.
    ///
    /// This is less expensive and less error prone than setTransform which may trigger a costly
    /// broadphase update and result in interpenetration.
    void changePositionAndRotation(const sead::Matrix34f& transform,
                                   float epsilon = sead::Mathf::epsilon());

    /// Modify the body's position by changing the linear velocity.
    /// This is preferable to setting the position directly (see changePositionAndRotation for an
    /// explanation).
    void changePosition(const sead::Vector3f& target_position, bool keep_angular_velocity,
                        float epsilon = sead::Mathf::epsilon());

    /// Modify the body's rotation by changing the angular velocity.
    /// This is preferable to setting the rotation directly (see changePositionAndRotation for an
    /// explanation).
    void changeRotation(const sead::Quatf& target_rotation, float epsilon = sead::Mathf::epsilon());
    /// Modify the body's rotation by changing the angular velocity.
    /// This is preferable to setting the rotation directly (see changePositionAndRotation for an
    /// explanation).
    void changeRotation(const sead::Matrix34f& rotation_matrix,
                        float epsilon = sead::Mathf::epsilon());

    /// Compute the angular velocity that would be necessary to instantly reach the target rotation.
    void computeAngularVelocity(hkVector4f* velocity, const hkQuaternionf& target_rotation,
                                float inv_delta_time) const;
    /// Compute the angular velocity that would be necessary to instantly reach the target rotation.
    void computeAngularVelocity(hkVector4f* velocity, const sead::Quatf& target_rotation) const;
    /// Compute the angular velocity that would be necessary to instantly reach the target rotation.
    void computeAngularVelocity(sead::Vector3f* velocity, const sead::Quatf& target_rotation) const;
    /// Compute the angular velocity that would be necessary to instantly reach the target rotation.
    void computeAngularVelocity(sead::Vector3f* velocity,
                                const sead::Matrix34f& rotation_matrix) const;

    /// Compute the linear velocity that would be necessary to instantly reach the target position.
    void computeLinearVelocity(hkVector4f* velocity, const hkVector4f& target_position,
                               const hkQuaternionf& rotation, float inv_delta_time) const;
    /// Compute the linear velocity that would be necessary to instantly reach the target position.
    void computeLinearVelocity(hkVector4f* velocity, const hkVector4f& target_position,
                               bool take_angular_velocity_into_account, float inv_delta_time) const;
    /// Compute the linear velocity that would be necessary to instantly reach the target position.
    void computeLinearVelocity(hkVector4f* velocity, const sead::Vector3f& target_position,
                               bool take_angular_velocity_into_account) const;
    /// Compute the linear velocity that would be necessary to instantly reach the target position.
    void computeLinearVelocity(sead::Vector3f* velocity, const sead::Vector3f& target_position,
                               bool take_angular_velocity_into_account) const;

    /// Compute the linear and angular velocities that would be necessary to instantly reach the
    /// target position and rotation.
    void computeVelocities(hkVector4f* linear_velocity, hkVector4f* angular_velocity,
                           const hkVector4f& position, const hkQuaternionf& rotation,
                           float inv_delta_time);
    /// Compute the linear and angular velocities that would be necessary to instantly reach the
    /// target position and rotation.
    void computeVelocities(hkVector4f* linear_velocity, hkVector4f* angular_velocity,
                           const hkVector4f& position, const hkQuaternionf& rotation);
    /// Compute the linear and angular velocities that would be necessary to instantly reach the
    /// target position and rotation.
    void computeVelocities(sead::Vector3f* linear_velocity, sead::Vector3f* angular_velocity,
                           const sead::Matrix34f& transform);

    float getInvDeltaTime() const;

    // endregion

    void setCenterOfMassInLocal(const sead::Vector3f& center);
    void getCenterOfMassInLocal(sead::Vector3f* center) const;
    sead::Vector3f getCenterOfMassInLocal() const;

    void getCenterOfMassInWorld(sead::Vector3f* center) const;
    sead::Vector3f getCenterOfMassInWorld() const;

    void setMaxLinearVelocity(float max);
    float getMaxLinearVelocity() const;

    void setMaxAngularVelocity(float max);
    float getMaxAngularVelocity() const;

    void applyLinearImpulse(const sead::Vector3f& impulse);
    void applyAngularImpulse(const sead::Vector3f& impulse);
    void applyPointImpulse(const sead::Vector3f& impulse, const sead::Vector3f& point);

    void setMass(float mass);
    float getMass() const;
    float getMassInv() const;

    void setInertiaLocal(const sead::Vector3f& inertia);
    void getInertiaLocal(sead::Vector3f* inertia) const;
    sead::Vector3f getInertiaLocal() const;

    /// Recalculate inertia, volume and center of mass based on the shape and mass of the rigid body
    /// and update this rigid body to match the computed values.
    virtual void resetInertiaAndCenterOfMass();

    /// All three parameters may be null.
    virtual void computeShapeVolumeMassProperties(float* volume, sead::Vector3f* center_of_mass,
                                                  sead::Vector3f* inertia_tensor);

    void setLinearDamping(float value);
    float getLinearDamping() const;

    void setAngularDamping(float value);
    float getAngularDamping() const;

    void setGravityFactor(float value);
    float getGravityFactor() const;

    virtual bool setTimeFactor(float value);
    float getTimeFactor() const;

    void setWaterBuoyancyScale(float scale);
    float getWaterBuoyancyScale() const;

    void setWaterFlowEffectiveRate(float rate);
    float getWaterFlowEffectiveRate() const;

    void setMagneMassScalingFactor(float factor);
    float getMagneMassScalingFactor() const;

    void setFrictionScale(float scale);
    float getFrictionScale() const;

    void setRestitutionScale(float scale);
    float getRestitutionScale() const;
    float getEffectiveRestitutionScale() const;

    void setMaxImpulse(float max);
    float getMaxImpulse() const;

    void setColImpulseScale(float scale);
    float getColImpulseScale() const;

    void clearEntityMotionFlag4(bool clear);
    bool isEntityMotionFlag4Off() const;

    void setEntityMotionFlag8(bool set);
    bool isEntityMotionFlag8On() const;

    void clearEntityMotionFlag10(bool clear);
    bool isEntityMotionFlag10Off() const;

    void clearEntityMotionFlag20(bool clear);
    bool isEntityMotionFlag20Off() const;

    void setEntityMotionFlag80(bool set);
    bool isEntityMotionFlag80On() const;

    bool isSensor() const { return mFlags.isOn(Flag::IsSensor); }
    bool isEntity() const { return !mFlags.isOn(Flag::IsSensor); }
    ContactLayerType getLayerType() const {
        return isSensor() ? ContactLayerType::Sensor : ContactLayerType::Entity;
    }

    bool hasFlag(Flag flag) const { return mFlags.isOn(flag); }
    const auto& getMotionFlags() const { return mMotionFlags; }
    void resetMotionFlagDirect(const MotionFlag flag) { mMotionFlags.reset(flag); }
    void setMotionFlag(MotionFlag flag);

    hkpRigidBody* getHkBody() const { return mHkBody; }

    Type getType() const { return mType; }
    bool isCharacterControllerType() const { return mType == Type::CharacterController; }

    UserTag* getUserTag() const { return mUserTag; }
    void setUserTag(UserTag* tag) { mUserTag = tag; }

    bool hasConstraintWithUserData();
    // 0x0000007100f94e80
    bool x_103(int a);
    // 0x0000007100f94f18
    bool x_104(RigidBody* other_body, int a, int b);
    // 0x0000007100f950ac
    bool x_105();

    void setEntityMotionFlag40(bool set);
    bool isEntityMotionFlag40On() const;

    // 0x0000007100f955c0 - FIXME: types
    void processUpdateRequests(void* data = nullptr, void* data2 = nullptr);

    void clearFlag2000000(bool clear);
    void clearFlag4000000(bool clear);
    void clearFlag8000000(bool clear);
    // 0x0000007100f95f8c
    void x_114(bool unk);

    void lock();
    void lock(bool also_lock_world);
    void unlock();
    void unlock(bool also_unlock_world);
    [[nodiscard]] auto makeScopedLock(bool also_lock_world) {
        return ScopedLock(this, also_lock_world);
    }
    [[nodiscard]] auto makeScopedLock() { return makeScopedLock(isAddedToWorld()); }

    hkpMotion* getMotion() const;

    // 0x0000007100f96a4c
    void x_123(bool unk);

    void setEntityMotionFlag1(bool set);
    bool isEntityMotionFlag1On() const;

    void setEntityMotionFlag100(bool set);
    bool isEntityMotionFlag100On() const;

    void setEntityMotionFlag200(bool set);
    bool isEntityMotionFlag200On() const;

    // FIXME: return type
    virtual u32 getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* shape_key,
                                  const sead::Vector3f& contact_point) = 0;

protected:
    /// Called whenever a shape update is requested.
    /// @return the new shape to use for the Havok rigid body or null to keep the current hkpShape
    virtual const hkpShape* getNewHavokShape_();

    virtual void* m11();

    /// @return the new scale
    virtual float updateScale_(float scale, float old_scale);

public:
    /// Called when the rigid body goes beyond the broadphase border.
    ///
    /// Note: this is not guaranteed to be called if we have a user tag.
    /// The tag may choose not to invoke this callback.
    ///
    /// The default implementation just resets the position to the origin.
    virtual void onMaxPositionExceeded();

    /// Get the name of this rigid body or its user.
    virtual const char* getName();

    RigidBodyContactCallback* getContactCallback() const { return mContactCallback; }
    void setContactCallback(RigidBodyContactCallback* cb) { mContactCallback = cb; }

    // Internal.
    void setUseSystemTimeFactor(bool use) { mFlags.change(Flag::UseSystemTimeFactor, use); }
    // Internal.
    void setFlag400000(bool set) { mFlags.change(Flag::_400000, set); }
    // Internal.
    void setUpdateRequestedFlag() { mFlags.set(Flag::UpdateRequested); }
    // Internal.
    void setFlag20() { mFlags.set(Flag::_20); }

    // Internal.
    void onCollisionAdded() {
        if (mCollisionCount.increment() == 0)
            clearFlag4000000(false);
    }

    // Internal.
    void onCollisionRemoved() {
        if (mCollisionCount.decrement() == 1)
            clearFlag4000000(true);
    }

protected:
    void createMotionAccessor(sead::Heap* heap);
    void assertLayerType(ContactLayer layer) const;
    void onInvalidParameter(int code = 0);
    void notifyUserTag(int code);
    void updateDeactivation();
    void setCollidableQualityType(hkpCollidableQualityType quality);

    sead::CriticalSection mCS;
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags{};
    sead::TypedBitFlag<MotionFlag, sead::Atomic<u32>> mMotionFlags{};
    sead::BitFlag32 mContactMask{};
    hkpRigidBody* mHkBody;
    UserTag* mUserTag = nullptr;
    ContactPointInfo* mContactPointInfo = nullptr;
    CollisionInfo* mCollisionInfo = nullptr;
    u16 _98 = 0;
    RigidBodyAccessor mRigidBodyAccessor;
    f32 mScale = 1.0f;
    Type mType{};
    MotionAccessor* mMotionAccessor = nullptr;
    sead::Atomic<int> mCollisionCount;
    RigidBodyContactCallback* mContactCallback = nullptr;
};
KSYS_CHECK_SIZE_NX150(RigidBody, 0xD0);

}  // namespace ksys::phys
