#pragma once

#include <basis/seadRawPrint.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/System/physLayerContactPointInfo.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Container/LockFreeQueue.h"
#include "KingSystem/Utils/Types.h"

class hkpEntity;

namespace ksys::phys {

class MotionAccessor;
class RigidBody;

class RigidBodyRequestMgr : public sead::hostio::Node {
public:
    struct Config {
        float _0 = 0.6;
        float _4 = 0.7;
        float _8 = 1.25;
        float _c = 1.0;
        float _10 = 0.2;
        float _14 = 0.9;
        float _18 = 0.5;
        float _1c = 1.0;
        float _20 = 4.0;
        // 5000m/s (squared)
        float linear_velocity_threshold_sq = 2.5e7;

        static Config& get();
        static bool isLinearVelocityTooHigh(const sead::Vector3f& velocity);
        static void enableLinearVelocityChecks(bool enable);
    };

    RigidBodyRequestMgr();
    virtual ~RigidBodyRequestMgr();

    void init(sead::Heap* heap);

    // 0x0000007100fa6ac4
    void calc(ContactLayerType layer_type);
    void calc1(ContactLayerType layer_type, bool paused);

    bool pushRigidBody(ContactLayerType type, RigidBody* body);
    void addEntityToWorld(ContactLayerType type, hkpEntity* entity);
    void removeEntityFromWorld(ContactLayerType type, hkpEntity* entity);
    // 0x0000007100fa6ebc
    void removeRigidBody(ContactLayerType type, RigidBody* body);

    bool onMaxPositionExceeded(ContactLayerType layer_type, RigidBody* body);

    bool addImpulse(RigidBody* body_a, RigidBody* body_b, float impulse);

    bool registerMotionAccessor(MotionAccessor* accessor);
    bool deregisterMotionAccessor(MotionAccessor* accessor);

private:
    struct Unk1;
    struct Unk3;

    struct Unk4 {
        u8 _0[0x10];
    };
    KSYS_CHECK_SIZE_NX150(Unk4, 0x10);

    struct ImpulseEntry {
        RigidBody* body_a;
        RigidBody* body_b;
        float impulse_a;
    };
    KSYS_CHECK_SIZE_NX150(ImpulseEntry, 0x18);

    struct Unk6 {
        sead::Vector3f _0 = sead::Vector3f::zero;
        u32 _c = 0x1000000;
        sead::Vector3f _10 = sead::Vector3f::zero;
        void* _20{};
        sead::Vector3f _28 = sead::Vector3f::ey;
        float _34{};
        sead::Vector3f _38 = sead::Vector3f::zero;
        float _44{};
    };
    KSYS_CHECK_SIZE_NX150(Unk6, 0x48);

    struct PointCallback : LayerContactPointInfo::ContactCallback {
        explicit PointCallback(RigidBodyRequestMgr* mgr_) : mgr(mgr_) {}

        bool invoke(const LayerContactPointInfo::ContactEvent& event) override {
            return mgr->someFunction2(event);
        }

        RigidBodyRequestMgr* mgr;
    };

    // FIXME: rename, implement
    bool someFunction2(const LayerContactPointInfo::ContactEvent& event);
    static void someFunction(void* arg);

    void processImpulseEntries();
    void processOobRigidBodyEntries(ContactLayerType layer_type);

    static constexpr int NumRigidBodyBuffers = 2;
    static constexpr int MaxNumImpulseEntries = 0x100;

    sead::SafeArray<util::LockFreeQueue<RigidBody>, NumRigidBodyBuffers> mRigidBodies1;
    util::LockFreeQueue<Unk1> _38;
    util::LockFreeQueue<Unk1> _50;
    /// Rigid bodies that are out of bounds.
    sead::SafeArray<util::LockFreeQueue<RigidBody>, NumRigidBodyBuffers> mOobRigidBodies;
    util::LockFreeQueue<ImpulseEntry> mImpulseEntries;
    util::LockFreeQueue<Unk3> _b0;
    util::LockFreeQueue<Unk4> _c8;
    util::LockFreeQueue<Unk4> _e0;
    sead::PtrArray<MotionAccessor> mMotionAccessors;
    sead::Buffer<ImpulseEntry> mImpulseEntriesPool;
    sead::Atomic<int> mNumActiveImpulseEntries;
    sead::Buffer<Unk6> _120;
    sead::Atomic<u32> _130;
    sead::Buffer<Unk4> _138;
    u32 mNumEntitiesInWorld{};
    LayerContactPointInfo* mContactPoints{};
    sead::SafeArray<sead::CriticalSection, NumRigidBodyBuffers> mCriticalSections;
    sead::CriticalSection mCS;
    float _218 = 1.0;
    float _21c = 1.0 / 30.0;
    float _220 = 1.0 / 30.0;
    float _224 = 1.0 / 30.0;
    float _228 = 1.0 / 30.0;
    sead::Atomic<u32> _22c;
    u32 mWaterIceSubmatIdx{};
    u32 mWaterHotSubmatIdx{};
    u32 mWaterPoisonSubmatIdx{};
    PointCallback mCallback{this};
    sead::Delegate1Func<void*> _250{&RigidBodyRequestMgr::someFunction};
};
KSYS_CHECK_SIZE_NX150(RigidBodyRequestMgr, 0x260);

}  // namespace ksys::phys
