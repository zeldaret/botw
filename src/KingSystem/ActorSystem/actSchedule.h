#pragma once
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"
namespace uking {
struct RoadNpcPlacementEntry;
}

namespace ksys::res {
class Handle;
}
namespace ksys::act {
class Actor;
namespace ai {
class RootAi;
}
class Schedule {
public:
    explicit Schedule(Actor* actor);
    virtual ~Schedule();
    virtual bool allocateResource(sead::Heap* heap);
    virtual void freeResource();

private:
    friend class ai::RootAi;
    friend struct uking::RoadNpcPlacementEntry;
    Actor* mActor;
    sead::FixedSafeString<64> mName;
    sead::SafeString _68;
    const char* _78;
    s32 _80;
    sead::SafeString _88;
    sead::SafeString _98;
    sead::SafeString _a8;
    sead::SafeString _b8;
    u32 _c8;
    BaseProcLink _d0;
    BaseProcLink _e0;
    BaseProcLink _f0;
    BaseProcLink _100;
    BaseProcLink _110;
    u8 mFlag120;
    u8 mFlag121;
    u8 mFlag122;
    u8 mFlag123;
    u8 mFlag124;
    u8 mFlag125;
    u8 mFlag126;
    u8 mFlag127;
    u8 mFlag128;
    u8 mFlag129;
    u8 mFlag12a;
    u8 mFlag12b;
    sead::Heap* mHeap;
    res::Handle* mResourceHandle;
    sead::SafeString _140;
    sead::SafeString _150;
    sead::SafeString _160;
    sead::SafeString _170;
    sead::SafeString _180;
    sead::SafeString _190;
    s32 mMoveReactionType;
    s32 mWaitReactionType;
    s32 mWaitRainReactionType;
    s32 mMeetingReactionType;
    s32 mMovePosture;
    s32 mWaitPosture;
    s32 mWaitRainPosture;
    s32 mMoveTalkTurn;
    s32 mWaitTalkTurn;
    s32 mWaitRainTalkTurn;
    s32 mReturnMoveTimeAfterTalk;
    s32 mReturnActionTimeAfterTalk;
    s32 mReturnActionRainTimeAfterTalk;
    s32 mReactionToApproachDist;
    sead::SafeString _1d8;
    sead::SafeString _1e8;
    sead::SafeString _1f8;
    sead::SafeString _208;
    sead::SafeString _218;
    sead::SafeString _228;
    sead::SafeString _238;
    sead::SafeString _248;
    sead::SafeString _258;
    sead::SafeString _268;
    sead::SafeString _278;
    sead::SafeString _288;
    sead::SafeString _298;
    sead::SafeString _2a8;
    sead::SafeString _2b8;
    sead::SafeString _2c8;
    sead::SafeString _2d8;
    f32 _2e8;
    u32 _2ec;
    u32 _2f0;
    sead::BitFlag32 _2f4;
    sead::BitFlag32 _2f8;
    s32 _2fc;
};
KSYS_CHECK_SIZE_NX150(Schedule, 0x300);
}  // namespace ksys::act
