#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/Types.h"

class hkpRigidBody;
class hkpMotion;

namespace ksys::phys {

class MotionAccessor;

class RigidBase {
public:
    virtual ~RigidBase();
};

class RigidBody : public sead::IDisposer, public RigidBase {
    SEAD_RTTI_BASE(RigidBody)
public:
    struct HkBodyMgr {
        explicit HkBodyMgr(hkpRigidBody* body);
        virtual ~HkBodyMgr();
        MotionType getMotionInfo() const;

        void* p;
    };

    enum class Flag1 {
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
    virtual ~RigidBody();

    void sub_7100F8CFA0();
    void setMotionFlag(MotionFlag);
    bool sub_7100F8D1F8() const;
    bool sub_7100F8D204() const;
    bool sub_7100F8D210() const;
    void sub_7100F8D21C();
    void sub_7100F8D680();
    MotionType getMotionInfo() const;
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

    bool isMassScaling() const { return mFlags.isOn(Flag1::MassScaling); }
    const auto& getMotionFlags() const { return mMotionFlags; }
    void resetMotionFlagDirect(const MotionFlag flag) { mMotionFlags.reset(flag); }

private:
    sead::CriticalSection mCS;
    sead::TypedBitFlag<Flag1, sead::Atomic<u32>> mFlags{};
    sead::TypedBitFlag<MotionFlag, sead::Atomic<u32>> mMotionFlags{};
    sead::BitFlag32 mContactMask{};
    hkpRigidBody* mHkBody;
    void* mActor = nullptr;
    void* _88 = nullptr;
    void* _90 = nullptr;
    u16 _98 = 0;
    HkBodyMgr mHkBodyMgr;
    f32 _b0 = 0.0f;
    u32 _b4;
    MotionAccessor* mMotionAccessor = nullptr;
    u16 _c0 = 0;
    void* _c8 = nullptr;
};
KSYS_CHECK_SIZE_NX150(RigidBody, 0xD0);

}  // namespace ksys::phys
