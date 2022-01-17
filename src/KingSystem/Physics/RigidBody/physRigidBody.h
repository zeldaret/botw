#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyAccessor.h"
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/Types.h"

class hkQuaternionf;
class hkVector4f;
class hkpRigidBody;
class hkpMaxSizeMotion;
class hkpMotion;

namespace ksys::phys {

class MotionAccessor;
struct RigidBodyInstanceParam;
class RigidBodyMotion;
class RigidBodyMotionProxy;
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
        MassScaling = 1 << 0,
        _2 = 1 << 1,
        _4 = 1 << 2,
        _8 = 1 << 3,
        _10 = 1 << 4,
        _20 = 1 << 5,
        _40 = 1 << 6,
        IsCharacterController = 1 << 7,
        _100 = 1 << 8,
        _200 = 1 << 9,
        _400 = 1 << 10,
        _800 = 1 << 11,
        _1000 = 1 << 12,
        _2000 = 1 << 13,
        _4000 = 1 << 14,
        _8000 = 1 << 15,
        _10000 = 1 << 16,
        _20000 = 1 << 17,
        _40000 = 1 << 18,
        _80000 = 1 << 19,
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

    RigidBody(Type type, u32 mass_scaling, hkpRigidBody* hk_body, const sead::SafeString& name,
              sead::Heap* heap, bool a7);
    ~RigidBody() override;

    // FIXME: types and names
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8(float);
    // FIXME: should be pure
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual const char* getName();

    bool initMotionAccessorForDynamicMotion(sead::Heap* heap);
    bool initMotionAccessor(const RigidBodyInstanceParam& param, sead::Heap* heap,
                            bool init_motion);
    /// Create a hkpMotion in the specified motion storage and initialise it.
    bool createMotion(hkpMaxSizeMotion* motion, MotionType motion_type,
                      const RigidBodyInstanceParam& param);

    sead::SafeString getHkBodyName() const;

    // 0x0000007100f8cfa0
    void x_0();

    bool isActive() const;

    bool isFlag8Set() const;
    bool isMotionFlag1Set() const;
    bool isMotionFlag2Set() const;
    void sub_7100F8D21C();
    // 0x0000007100f8d308
    bool x_6();

    /// Get the motion accessor if it is a RigidBodyMotion. Returns nullptr otherwise.
    RigidBodyMotion* getMotionAccessor() const;
    /// Get the motion accessor if it is a RigidBodyMotion. Returns nullptr otherwise.
    /// For internal use by the physics system.
    RigidBodyMotion* getMotionAccessorForProxy() const;

    /// Get the motion accessor if it is a RigidBodyMotionProxy. Returns nullptr otherwise.
    RigidBodyMotionProxy* getMotionProxy() const;
    /// Get the linked rigid body from the motion proxy (or nullptr if there is none).
    RigidBody* getLinkedRigidBody() const;
    /// Reset the linked rigid body if we have a motion proxy.
    void resetLinkedRigidBody() const;

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

    // 0x0000007100f8e7e8
    void x_13(bool a, bool b);
    // 0x0000007100f8e8f0
    void x_14(bool a, bool b, bool c);
    // 0x0000007100f8eabc
    void x_15(bool a, bool b);
    // 0x0000007100f8ee38
    void resetFrozenState();

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

    void getPosition(sead::Vector3f* position) const;
    sead::Vector3f getPosition() const;

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

    // 0x0000007100f91264
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
    // 0x0000007100f93498
    float getMassInv() const;

    // 0x0000007100f93534
    void setInertiaLocal(const sead::Vector3f& inertia);
    // 0x0000007100f935dc
    void getInertiaLocal(sead::Vector3f* inertia) const;
    // 0x0000007100f9368c
    sead::Vector3f getInertiaLocal() const;

    // 0x0000007100f93750
    void setLinearDamping(float value);
    // 0x0000007100f93804
    float getLinearDamping() const;
    // 0x0000007100f938a0
    void setAngularDamping(float value);
    // 0x0000007100f93954
    float getAngularDamping() const;
    // 0x0000007100f939f0
    void setGravityFactor(float value);
    // 0x0000007100f93a9c
    float getGravityFactor() const;

    bool isMassScaling() const { return mFlags.isOn(Flag::MassScaling); }
    bool hasFlag(Flag flag) const { return mFlags.isOn(flag); }
    const auto& getMotionFlags() const { return mMotionFlags; }
    void resetMotionFlagDirect(const MotionFlag flag) { mMotionFlags.reset(flag); }
    void setMotionFlag(MotionFlag flag);

    hkpRigidBody* getHkBody() const { return mHkBody; }

    Type getType() const { return mType; }
    bool isCharacterControllerType() const { return mType == Type::CharacterController; }

    // 0x0000007100f969a0
    void lock(bool also_lock_world);
    // 0x0000007100f969e8
    void unlock(bool also_unlock_world);

    hkpMotion* getMotion() const;

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

    [[nodiscard]] auto makeScopedLock(bool also_lock_world) {
        return ScopedLock(this, also_lock_world);
    }

private:
    ContactLayerType getLayerType() const {
        return !isMassScaling() ? ContactLayerType::Entity : ContactLayerType::Sensor;
    }

    void createMotionAccessor(sead::Heap* heap);
    void onInvalidParameter(int code = 0);
    void notifyUserTag(int code);

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
    u16 _c0 = 0;
    u16 _c2 = 0;
    void* _c8 = nullptr;
};
KSYS_CHECK_SIZE_NX150(RigidBody, 0xD0);

}  // namespace ksys::phys
