#pragma once

#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <math/seadBoundBox.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <xlink2/xlink2.h>
#include "KingSystem/ActorSystem/actActorEditorNode.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcJobHandler.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actPhysicsConstraints.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Utils/AtomicLongBitFlag.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"

namespace gsys {
class Model;
}  // namespace gsys

namespace ksys {

namespace as {
class ASList;
}  // namespace as

namespace map {
class Object;
}  // namespace map

namespace mii {
class HylianInfo;
class UMii;
}  // namespace mii

namespace phys {
class StaticCompoundRigidBodyGroup;
class Physics;
class Reaction;
class RigidBody;
}  // namespace phys

namespace res {
class Handle;
}  // namespace res

namespace xlink {
class XLink;
}  // namespace xlink

namespace act {

namespace ai {
class RootAi;
}

class LifeRecoverInfo;
class Actor;
class ActorCreator;
class ActorParam;
class Attention;
class Awareness;
class BaseProcLink;
class BoneControl;
class Chemical;
class ImpulseBaseProcLink;
class ModelBindInfo;
class Schedule;

// FIXME: move this to a separate file and rename
class UMiiModelLink {
public:
    explicit UMiiModelLink(Actor* actor) : mActor(actor) {}

    virtual void m0() {}
    virtual void m1() {}
    virtual void m2() {}
    virtual void m3() {}

private:
    Actor* mActor = nullptr;
};
KSYS_CHECK_SIZE_NX150(UMiiModelLink, 0x10);

struct ActorUniqueName {
    sead::BufferedSafeString* unique_name;
    sead::FixedSafeString<16> change_attention_type;
};
KSYS_CHECK_SIZE_NX150(ActorUniqueName, 0x30);

class Actor : public BaseProc, public ActorMessageTransceiver::IHandler {
public:
    enum class StasisFlag {
        _1 = 1,
        _2 = 2,
        _4 = 4,
    };

    enum class ActorFlag {
        _18 = 0x18,
        _25 = 0x25,
        _29 = 0x29,
        _2b = 0x2b,
        _2e = 0x2e,
        _39 = 0x39,
    };

    enum class ActorFlag2 {
        InstEvent = 0x8,
        NoDistanceCheck = 0x80,
        Alive = 0x4000000,
    };

    enum class DeleteType {
        _1 = 1,
        _2 = 2,
        _3 = 3,
    };

    explicit Actor(const CreateArg& arg);
    ~Actor() override;

    SEAD_RTTI_OVERRIDE(Actor, BaseProc)

public:
    const sead::SafeString& getProfile() const;
    const char* getUniqueName() const;

    ai::RootAi* getRootAi() const { return mRootAi; }
    const ActorParam* getParam() const { return mActorParam; }
    map::Object* getMapObject() const { return mMapObject; }
    const map::MubinIter& getMapObjIter() const { return mMapObjIter; }

    const sead::Matrix34f& getMtx() const { return mMtx; }
    const sead::Vector3f& getVelocity() const { return mVelocity; }
    const sead::Vector3f& getAngVelocity() const { return mAngVelocity; }
    const sead::Vector3f& getScale() const { return mScale; }
    f32 getDeleteDistance() const {
        return sead::Mathf::sqrt(sead::Mathf::clampMin(mDeleteDistanceSq, 0.0f));
    }

    void setDeleteDistance(f32 distance) { mDeleteDistanceSq = sead::Mathf::square(distance); }

    void clearFlag(ActorFlag flag);
    bool checkFlag(ActorFlag flag) const;
    void setFlag(ActorFlag flag);
    void setFlag(ActorFlag flag, bool on);
    bool deleteEx(DeleteType type, DeleteReason reason, bool* ok = nullptr);

    void setProperties(int x, const sead::Matrix34f& mtx, const sead::Vector3f& vel,
                       const sead::Vector3f& ang_vel, const sead::Vector3f& scale,
                       bool is_life_infinite, int i, int life) const;

    // FIXME: figure out return types, parameters and names
    virtual s32 getMaxLife();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void getGuardableAngle();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void killWithDropsAndEffects();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void onPreFadeOutDelete();
    virtual void onFadeOutSleep();
    virtual void m60();
    virtual void m61();
    virtual bool shouldUnload();
    virtual void m63();
    virtual void initMaybe();
    virtual void updateLodStuff();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void calcMaybe();
    virtual void m70();
    virtual void updatePositionMaybe();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void afterModelMatrixUpdate();
    virtual void m79();
    virtual bool m80();
    virtual void m81();
    virtual int getCalcTiming();
    virtual void m83();
    virtual void updateMtxFromPhysics();
    virtual void setMtx();
    virtual void m86();
    virtual s32* getLife();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91();
    virtual void m92();
    virtual void m93();
    virtual void m94();
    virtual void m95();
    virtual void m96();
    virtual void getChemicalStuff();
    virtual void getWeapons();
    virtual void getArmors();
    virtual void m100();
    virtual void m101();
    virtual int getExtraHeapSize();
    virtual void m103();
    int handleMessage(const Message& message) override;
    void handleAck(const MessageAck& ack) override;
    virtual void m106();
    virtual void m107();
    virtual void m108();
    virtual void m109();
    virtual void m110();
    virtual void m111();
    virtual void m112();
    virtual void m113();
    virtual void m114();
    virtual void m115();
    virtual void m116();
    virtual void m117();
    virtual void m118();
    virtual void m119();
    virtual void m120();
    virtual void m121();
    virtual void m122();
    virtual void m123();
    virtual void onPlacementObjReset();
    virtual void getAtk();
    virtual void m126();
    virtual void getDamageMgr();
    virtual void m128();
    virtual void m129();
    virtual void getPlayerRideInfo();
    virtual void getHorseOptionsMaybe();
    virtual void m132();
    virtual void getMotorcyclePriorityStuffMaybe();
    virtual void getDropData();
    virtual void m135();
    virtual LifeRecoverInfo* getLifeRecoverInfo();
    virtual void m137();
    virtual void m138();
    virtual void m139();
    virtual void m140();
    virtual void m141();
    virtual void m142();
    virtual void m143();
    virtual void m144();
    virtual void m145();
    virtual void m146();
    virtual void m147();

    void emitBasicSigOn();
    void emitBasicSigOff();

    void nullsub_4649();  // Some kind of logging which has been excluded from the build?

    sead::TypedBitFlag<ActorFlag2>& getActorFlags2() { return mActorFlags2; }
    const sead::TypedBitFlag<ActorFlag2>& getActorFlags2() const { return mActorFlags2; }

    void onAiEnter(const char* name, const char* context);

    static constexpr size_t getCreatorListNodeOffset() {
        return offsetof(Actor, mCreatorActorListNode);
    }

protected:
    friend class ActorCreator;

    struct Unk1 {
        Actor* actor;
        u32 _4;
    };

    struct Unk2 {
        s16 _0 = -1;
        s16 _2 = -1;
    };

    // FIXME: rename
    void job0_1();
    void job0_2();
    void job1_1();
    void job1_2();
    void job2_1();
    void job2_2();
    void job4();

    /* 0x190 */ sead::Atomic<phys::RigidBody*> mMainBody = nullptr;
    /* 0x198 */ sead::Atomic<phys::RigidBody*> mTgtBody = nullptr;
    /* 0x1a0 */ void* _1a0 = nullptr;
    /* 0x1a8 */ void* _1a8 = nullptr;
    /* 0x1b0 */ Unk1 mUnk1;
    /* 0x1c0 */ u32 _1c0 = 3;

    /* 0x1c8 */ BaseProcJobHandlerDualT<Actor> mJob0{this, &Actor::job0_1, &Actor::job0_2};
    /* 0x238 */ BaseProcJobHandlerDualT<Actor> mJob1{this, &Actor::job1_1, &Actor::job1_2};
    /* 0x2a8 */ BaseProcJobHandlerDualT<Actor> mJob2{this, &Actor::job2_1, &Actor::job2_2};
    /* 0x318 */ BaseProcJobHandlerT<Actor> mJob4{this, &Actor::job4};

    /* 0x368 */ sead::ListNode mActiveActorListNode;
    /* 0x378 */ sead::ListNode mActorsThatLostPlacementObjListNode;
    /* 0x388 */ sead::ListNode mVillagerListNode;

    /* 0x398 */ sead::Matrix34f mMtx = sead::Matrix34f::ident;
    /* 0x3c8 */ sead::Matrix34f* mPhysicsMtx = nullptr;
    /* 0x3d0 */ sead::Matrix34f mHomeMtx = sead::Matrix34f::ident;
    /* 0x400 */ sead::Vector3f mVelocity{0, 0, 0};
    /* 0x40c */ sead::Vector3f mAngVelocity{0, 0, 0};
    /* 0x418 */ sead::Vector3f mScale{1, 1, 1};
    /* 0x424 */ float mDispDistanceSq;
    /* 0x428 */ float mDeleteDistanceSq = -1.0;
    /* 0x42c */ float mLoadDistance = -1.0;
    /* 0x430 */ sead::Vector3f mPreviousPos{0, 0, 0};
    /* 0x43c */ sead::Vector3f mPreviousPos2{0, 0, 0};
    /* 0x448 */ sead::Vector3f _448{0, 0, 0};
    /* 0x454 */ sead::Vector3f _454{0, 0, 0};
    /* 0x460 */ sead::Vector3f _460{0, 0, 0};
    /* 0x46c */ sead::Vector3f _46c{0, 0, 0};
    /* 0x478 */ sead::Vector3f _478;
    /* 0x484 */ sead::Vector3f mPreviousPos3{0, 0, 0};
    /* 0x490 */ float _490 = 0.0;
    /* 0x494 */ float _494 = 0.0;
    /* 0x498 */ Unk2 _498;
    /* 0x49c */ Unk2 _49c;
    /* 0x4a0 */ s16 _4a0 = -1;
    /* 0x4a2 */ s16 _4a2 = -1;
    /* 0x4a4 */ s16 _4a4 = -1;
    /* 0x4a6 */ s16 _4a6 = -1;
    /* 0x4a8 */ s16 _4a8 = -1;
    /* 0x4aa */ s16 _4aa = -1;
    /* 0x4ac */ s16 _4ac = -1;
    /* 0x4ae */ s16 _4ae = -1;
    /* 0x4b0 */ s16 _4b0 = -1;
    /* 0x4b2 */ s16 _4b2 = -1;
    /* 0x4b4 */ sead::Vector3f _4b4{0, 0, 0};
    /* 0x4c0 */ sead::Vector3f mEnterCalcPos{0, 0, 0};

    /* 0x4d0 */ ModelBindInfo* mModelBindInfo = nullptr;
    /* 0x4d8 */ void* _4d8 = nullptr;
    /* 0x4e0 */ gsys::Model* mModel = nullptr;
    /* 0x4e8 */ float _4e8 = 1.0;
    /* 0x4ec */ float mStartModelOpacity = 0.0;
    /* 0x4f0 */ float _4f0 = 1.0;
    /* 0x4f4 */ float _4f4 = 0.0;
    /* 0x4f8 */ float _4f8 = 0.0;
    /* 0x4fc */ float _4fc = 0.0;
    /* 0x500 */ sead::BoundBox3f mAabb{sead::Vector3f::zero, sead::Vector3f::zero};

    /* 0x518 */ sead::TypedBitFlag<ActorFlag2> mActorFlags2{};
    /* 0x51c */ sead::TypedBitFlag<ActorFlag2> mActorFlags2Prev{};
    /* 0x520 */ util::AtomicLongBitFlag<64, ActorFlag> mActorFlags{};

    /* 0x528 */ PhysicsUserTag mPhysicsUserTag{this};
    /* 0x540 */ sead::Atomic<bool> _540 = false;

    /* 0x548 */ void* _548 = nullptr;
    /* 0x550 */ Awareness* mAwareness = nullptr;
    /* 0x558 */ ai::RootAi* mRootAi = nullptr;
    /* 0x560 */ as::ASList* mASList = nullptr;
    /* 0x568 */ xlink::XLink* mXLink = nullptr;
    /* 0x570 */ ActorParam* mActorParam = nullptr;
    /* 0x578 */ phys::Physics* mPhysics = nullptr;
    /* 0x580 */ PhysicsConstraints mConstraints;
    /* 0x598 */ void* _598 = nullptr;
    /* 0x5a0 */ BoneControl* mBoneControl = nullptr;
    /* 0x5a8 */ phys::StaticCompoundRigidBodyGroup* mFieldBodyGroup = nullptr;
    /* 0x5b0 */ void* _5b0 = nullptr;
    /* 0x5b8 */ sead::Heap* mDualHeap = nullptr;   // TODO: rename
    /* 0x5c0 */ sead::Heap* mDualHeap2 = nullptr;  // TODO: rename
    /* 0x5c8 */ sead::Heap* mHeap = nullptr;       // TODO: rename
    /* 0x5d0 */ ActorUniqueName* mUniqueName = nullptr;
    /* 0x5d8 */ Attention* mAttention = nullptr;
    /* 0x5e0 */ ActorMessageTransceiver mMsgTransceiver{*this, this};
    /* 0x638 */ Schedule* mSchedule = nullptr;

    /* 0x640 */ u32 mHashId = 0;
    /* 0x648 */ map::MubinIter mMapObjIter;

    /* 0x658 */ xlink2::Handle _658;
    /* 0x668 */ xlink2::Handle _668;
    /* 0x678 */ res::Handle* mModelResMaybe = nullptr;
    /* 0x680 */ u8 _680 = 0;
    /* 0x681 */ u8 _681 = 0;
    /* 0x682 */ u8 _682 = 0;
    /* 0x683 */ u8 _683 = 0;
    /* 0x684 */ u8 mSkipJobPushTimer = 0;
    /* 0x685 */ sead::BitFlag8 mSpecialJobTypesMaskOverride;
    /* 0x686 */ s8 _686 = -1;
    /* 0x687 */ sead::Atomic<bool> _687 = false;
    /* 0x688 */ sead::Atomic<bool> mLifeInfiniteMaybe = false;
    /* 0x689 */ sead::Atomic<bool> _689 = false;
    /* 0x68a */ sead::Atomic<bool> _68a = false;
    /* 0x68b */ sead::Atomic<bool> mNoFadeInCreate = false;
    /* 0x68c */ sead::Atomic<bool> _68c = false;
    /* 0x68d */ sead::Atomic<bool> _68d = false;
    /* 0x68e */ sead::Atomic<bool> _68e = false;
    /* 0x68f */ sead::Atomic<bool> _68f = false;
    /* 0x690 */ bool _690 = false;
    /* 0x691 */ bool _691 = false;
    /* 0x694 */ sead::Atomic<int> mFadeOutDeleteType = 0;
    /* 0x698 */ sead::Atomic<u32> mFadeOutSleepFlags;
    /* 0x6a0 */ void* _6a0 = nullptr;
    /* 0x6a8 */ Chemical* mChemical = nullptr;
    /* 0x6b0 */ phys::Reaction* mReaction = nullptr;
    /* 0x6b8 */ void* _6b8 = nullptr;
    /* 0x6c0 */ UMiiModelLink mUMiiModelLink{this};
    /* 0x6d0 */ float _6d0 = 0.0;
    /* 0x6d8 */ void* _6d8 = nullptr;
    /* 0x6e0 */ float _6e0 = 0.0;
    /* 0x6e4 */ float _6e4 = 0.0;
    /* 0x6e8 */ float _6e8 = -1.0;
    /* 0x6ec */ int _6ec = 0;
    /* 0x6f0 */ float _6f0 = -1.0;
    /* 0x6f4 */ float _6f4 = 0.0;
    /* 0x6f8 */ float _6f8 = 0.0;
    /* 0x6fc */ int _6fc = 0;
    /* 0x700 */ int _700 = 0;
    /* 0x708 */ ImpulseBaseProcLink* mImpulseBaseProcLink = nullptr;
    /* 0x710 */ sead::TypedBitFlag<StasisFlag> mStasisFlags;  // TODO: probably need to rename this
    /* 0x714 */ float mLodLoadDistanceMultiplier = 1.0;
    /* 0x718 */ float _718 = 0.0;
    /* 0x71c */ sead::BitFlag32 mSignals;
    /* 0x720 */ sead::BitFlag32 _720;
    /* 0x728 */ void* _728 = nullptr;
    /* 0x730 */ u16 _730 = 0;
    /* 0x732 */ sead::BitFlag16 mDrawDistanceFlags;
    /* 0x738 */ BaseProcLink _738;
    /* 0x748 */ BaseProcLink mCreateArgBaseProcLink;
    /* 0x758 */ void* _758 = nullptr;
    /* 0x760 */ xlink2::Handle _760;
    /* 0x770 */ xlink2::Handle _770;
    /* 0x780 */ xlink2::Handle mSwordBlurHandle;
    /* 0x790 */ xlink2::Handle _790;
    /* 0x7a0 */ sead::Vector3f _7a0 = sead::Vector3f::zero;

    /* 0x7b0 */ ActorCreator* mCreator{};
    /* 0x7b8 */ sead::ListNode mCreatorActorListNode;
    /* 0x7c8 */ map::Object* mMapObject{};

    /* 0x7d0 */ void* _7d0 = nullptr;
    /* 0x7d8 */ bool _7d8 = false;

    /* 0x7e0 */ ActorEditorNode mActorEditorNode;
    /* 0x810 */ sead::Buffer<void*> mUMiiBones;  // FIXME: type
    /* 0x820 */ mii::UMii* mUMii = nullptr;
    /* 0x828 */ mii::HylianInfo* mUMiiHylianInfo = nullptr;

    /* 0x830 */ float _830 = 1.0;
    /* 0x834 */ int _834 = 0;
    /* 0x838 */ int _838 = 0;

private:
    enum class HandleMessageResult {
        _0,
        _1,
        _2,
    };

    HandleMessageResult doHandleMessage_(const Message& message);
};
KSYS_CHECK_SIZE_NX150(Actor, 0x840);

BaseProcLink& getDummyBaseProcLink();

}  // namespace act

}  // namespace ksys
