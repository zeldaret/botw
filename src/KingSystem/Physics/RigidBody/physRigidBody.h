#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyAccessor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/Types.h"

class hkpRigidBody;
class hkpMotion;

namespace ksys::phys {

class MotionAccessor;
class RigidContactPoints;
class UserTag;

class RigidBase {
public:
    virtual ~RigidBase() = 0;
};

class RigidBody : public sead::IDisposer, public RigidBase {
    SEAD_RTTI_BASE(RigidBody)
public:
    enum class Flag {
        MassScaling = 1 << 0,
        _2 = 1 << 1,
        _4 = 1 << 2,
        _8 = 1 << 3,
        _10 = 1 << 4,
        _20 = 1 << 5,
        _40 = 1 << 6,
        _80 = 1 << 7,
        _100 = 1 << 8,
    };

    enum class MotionFlag {
        _1 = 1 << 0,
        _2 = 1 << 1,
        Dynamic = 1 << 2,
        Keyframed = 1 << 3,
        Fixed = 1 << 4,
        _20 = 1 << 5,
    };

    RigidBody(u32 a, u32 mass_scaling, hkpRigidBody* hk_body, const sead::SafeString& name,
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
    virtual void m14();

    // 0x0000007100f8ca50
    bool initMotionAccessor(sead::Heap* heap);
    // 0x0000007100f8cc98
    void initMotionAndAccessor();
    // 0x0000007100f8cd44
    void initMotion();

    sead::SafeString getName() const;

    // 0x0000007100f8cfa0
    void x_0();

    void setMotionFlag(MotionFlag);

    bool isActive() const;

    // 0x0000007100f8d1f8
    bool sub_7100F8D1F8() const;
    // 0x0000007100f8d204
    bool sub_7100F8D204() const;
    // 0x0000007100f8d210
    bool sub_7100F8D210() const;
    // 0x0000007100f8d21c
    void sub_7100F8D21C();
    // 0x0000007100f8d308
    bool x_6();

    // 0x0000007100f8d680
    // FIXME: rename after we figure out what the two types of MotionAccessor are
    MotionAccessor* getMotionAccessorType1();
    // 0x0000007100f8d70c
    void* getMotionAccessorType2Stuff();
    // 0x0000007100f8d7a8
    void motionAccessorType2Stuff2();
    // 0x0000007100f8d840
    void x_8();

    MotionType getMotionInfo() const;

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
    // 0x0000007100f8ec3c
    bool setLinearVelocityMaybe(const sead::Vector3f& velocity, float x);
    // 0x0000007100f8ed74
    bool setAngularVelocityMaybe(const sead::Vector3f& velocity, float x);
    // 0x0000007100f8ee38
    void x_16();

    u32 addContactLayer(ContactLayer);
    u32 removeContactLayer(ContactLayer);
    void setContactMask(u32);
    void setContactAll();
    void setContactNone();
    void setCollideGround(bool);
    void setCollideWater(bool);
    void sub_7100F8F51C();
    void sub_7100F8F8CC(ContactLayer, GroundHit, void*);
    void sub_7100F8F9E8(u32*, void*);
    void sub_7100F8FA44(ContactLayer, u32);
    hkpMotion* getMotion() const;

    bool isMassScaling() const { return mFlags.isOn(Flag::MassScaling); }
    const auto& getMotionFlags() const { return mMotionFlags; }
    void resetMotionFlagDirect(const MotionFlag flag) { mMotionFlags.reset(flag); }

private:
    sead::CriticalSection mCS;
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags{};
    sead::TypedBitFlag<MotionFlag, sead::Atomic<u32>> mMotionFlags{};
    sead::BitFlag32 mContactMask{};
    hkpRigidBody* mHkBody;
    UserTag* mUserTag = nullptr;
    void* _88 = nullptr;
    void* _90 = nullptr;
    u16 _98 = 0;
    RigidBodyAccessor mRigidBodyAccessor;
    f32 _b0 = 1.0f;
    u32 _b4 = 0;
    MotionAccessor* mMotionAccessor = nullptr;
    u16 _c0 = 0;
    u16 _c2 = 0;
    void* _c8 = nullptr;
};
KSYS_CHECK_SIZE_NX150(RigidBody, 0xD0);

}  // namespace ksys::phys
