#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <math/seadBoundBox.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyAccessor.h"
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/Types.h"

enum hkpCollidableQualityType : int;
class hkQuaternionf;
class hkVector4f;
class hkpRigidBody;
class hkpMaxSizeMotion;
class hkpMotion;

namespace ksys::phys {

class MotionAccessor;
struct RigidBodyInstanceParam;
class RigidBodyMotionEntity;
class RigidBodyMotionSensor;
class RigidContactPoints;
class UserTag;

class RigidBase {
public:
    virtual ~RigidBase() = default;
};

class RigidBody : public sead::IDisposer, public RigidBase {
    SEAD_RTTI_BASE(RigidBody)
public:
    enum class Type {
        _0 = 0,
        _1 = 1,
        _2 = 2,
        TerrainHeightField = 3,
        _4 = 4,
        CharacterController = 5,
        TeraMesh = 6,
    };

    enum class Flag {
        IsSensor = 1 << 0,
        UpdateRequested = 1 << 1,
        _4 = 1 << 2,
        _8 = 1 << 3,
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
    };

    enum class MotionFlag {
        _1 = 1 << 0,
        _2 = 1 << 1,
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
        _4000 = 1 << 14,
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
              const sead::SafeString& name, sead::Heap* heap, bool a7);
    ~RigidBody() override;

    virtual float m4();

    bool initMotionAccessorForDynamicMotion(sead::Heap* heap);
    bool initMotionAccessor(const RigidBodyInstanceParam& param, sead::Heap* heap,
                            bool init_motion);
    /// Create a hkpMotion in the specified motion storage and initialise it.
    bool createMotion(hkpMaxSizeMotion* motion, MotionType motion_type,
                      const RigidBodyInstanceParam& param);

    sead::SafeString getHkBodyName() const;

    void x_0();

    bool isActive() const;

    bool isFlag8Set() const;
    bool isMotionFlag1Set() const;
    bool isMotionFlag2Set() const;
    void sub_7100F8D21C();
    // 0x0000007100f8d308
    bool x_6();

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
    void x_8();

    MotionType getMotionType() const;

    // Motion functions
    // 0x0000007100f8dcfc
    void x_9();
    // 0x0000007100f8e110
    void x_10();
    // 0x0000007100f8e3fc
    void x_11();

    // 0x0000007100f8e72c
    void x_12();
    // 0x0000007100f8e7b4
    void setContactPoints(RigidContactPoints* points);

    void freeze(bool should_freeze, bool preserve_velocities, bool preserve_max_impulse);
    void setFixedAndPreserveImpulse(bool fixed, bool mark_linear_vel_as_dirty);
    void setFixed(bool fixed, bool preserve_velocities);
    void resetFrozenState();

    void updateCollidableQualityType(bool high_quality);

    u32 addContactLayer(ContactLayer);
    u32 removeContactLayer(ContactLayer);
    void setContactMask(u32);
    void setContactAll();
    void setContactNone();
    void setCollideGround(bool);
    void setCollideWater(bool);
    void sub_7100F8F51C();
    void sub_7100F8F8CC(ContactLayer, GroundHit, void*);
    void sub_7100F8F9E8(ReceiverMask*, void*);
    void sub_7100F8FA44(ContactLayer, u32);

    void setPosition(const sead::Vector3f& position, bool propagate_to_linked_motions);
    void getPosition(sead::Vector3f* position) const;
    sead::Vector3f getPosition() const;
    virtual void logPosition() const;
    void getAabbInLocal(sead::BoundBox3f* aabb) const;
    void getAabbInWorld(sead::BoundBox3f* aabb) const;

    void getRotation(sead::Quatf* rotation) const;
    sead::Quatf getRotation() const;

    void getPositionAndRotation(sead::Vector3f* position, sead::Quatf* rotation) const;

    void getTransform(sead::Matrix34f* mtx) const;
    sead::Matrix34f getTransform() const;
    // 0x0000007100f8fb08
    void setTransform(const sead::Matrix34f& mtx, bool propagate_to_linked_motions);

    bool setLinearVelocity(const sead::Vector3f& velocity, float epsilon = sead::Mathf::epsilon());
    void getLinearVelocity(sead::Vector3f* velocity) const;
    sead::Vector3f getLinearVelocity() const;

    bool setAngularVelocity(const sead::Vector3f& velocity, float epsilon = sead::Mathf::epsilon());
    void getAngularVelocity(sead::Vector3f* velocity) const;
    sead::Vector3f getAngularVelocity() const;

    void getPointVelocity(sead::Vector3f* velocity, const sead::Vector3f& point) const;

    // 0x0000007100f92b74
    void computeVelocities(hkVector4f* linear_velocity, hkVector4f* angular_velocity,
                           const hkVector4f& position, const hkQuaternionf& rotation);

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

    bool hasConstraintWithUserData();
    // 0x0000007100f94e80
    bool x_103(int a);
    // 0x0000007100f94f18
    bool x_104(RigidBody* other_body, int a, int b);
    // 0x0000007100f950ac
    bool x_105();

    void setEntityMotionFlag40(bool set);
    bool isEntityMotionFlag40On() const;

    void clearFlag2000000(bool clear);
    void clearFlag4000000(bool clear);
    void clearFlag8000000(bool clear);

    void lock();
    void lock(bool also_lock_world);
    void unlock();
    void unlock(bool also_unlock_world);
    [[nodiscard]] auto makeScopedLock(bool also_lock_world) {
        return ScopedLock(this, also_lock_world);
    }

    hkpMotion* getMotion() const;

    void setEntityMotionFlag1(bool set);
    bool isEntityMotionFlag1On() const;

    void setEntityMotionFlag100(bool set);
    bool isEntityMotionFlag100On() const;

    void setEntityMotionFlag200(bool set);
    bool isEntityMotionFlag200On() const;

    virtual void m9() = 0;
    virtual void* m10();
    virtual void* m11();
    virtual float m12(float x, float y);
    virtual void resetPosition();
    virtual const char* getName();

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

private:
    void createMotionAccessor(sead::Heap* heap);
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
    RigidContactPoints* mContactPoints = nullptr;
    void* _90 = nullptr;
    u16 _98 = 0;
    RigidBodyAccessor mRigidBodyAccessor;
    f32 _b0 = 1.0f;
    Type mType{};
    MotionAccessor* mMotionAccessor = nullptr;
    sead::Atomic<int> mCollisionCount;
    void* _c8 = nullptr;
};
KSYS_CHECK_SIZE_NX150(RigidBody, 0xD0);

}  // namespace ksys::phys
