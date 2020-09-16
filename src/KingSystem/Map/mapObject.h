#pragma once

#include <basis/seadTypes.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class BaseProc;
}

namespace ksys::map {

class LinkData;

// FIXME: incomplete
class Object {
public:
    // TODO: rename
    enum class Flag0 {

    };

    enum class Flag {
        IsLinkTag = 0x1,
        IncrementSave = 0x2,
        IsLinkTagNAndOrNOr = 0x4,
        _8 = 0x8,
        ShapeCapsuleOrCylinder = 0x10,
        SheikSensorTargetDeadOrAlive = 0x20,
        UnderGodForest = 0x40,
        UnderGodForestOff = 0x80,
        CreateNotRain = 0x100,
        ActorCreated = 0x200,
        HasTraversePos = 0x400,
        HasUniqueName = 0x800,
        IsCreateSharpWeapon = 0x1000,
        // TODO: rename this. This name is too long...
        IsTurnActorBowChargeAndHasBasicSigLink = 0x8000,
    };

    // TODO: rename
    enum class ActorFlag8 {

    };

    enum class HardModeFlag {
        ActorCreated = 0x1,
        /// This actor only spawns in master mode (hard mode).
        IsHardModeActor = 0x2,
        /// This actor only spawns during the One-Hit Obliterator (Ichigeki/一撃) challenge.
        IsOneHitChallengeActor = 0x4,
        /// This actor does not rank up in master mode.
        DisableRankup = 0x8,
    };

    Object();
    ~Object();

    auto getFlags0() const { return mFlags0; }
    auto getFlags() const { return mFlags; }
    auto getActorFlags8() const { return mActorFlags8; }
    auto getHardModeFlags() const { return mHardModeFlags; }

    auto getActorDataIdx() const { return mActorDataIdx; }
    auto getIdx() const { return mIdx; }
    auto getId() const { return mId; }
    auto getStaticCompoundId() const { return mStaticCompoundId; }

    u8 getNumLinksPointingToMe() const { return mNumLinksPointingToMe; }

    const MubinIter& getMubinIter() const { return mMubinIter; }
    act::BaseProc* getProc() const { return mProc; }
    LinkData* getLinkData() const { return mLinkData; }

    u32 getRevivalGameDataFlagHash() const { return mRevivalGameDataFlagHash; }
    u32 getHashId() const { return mHashId; }

    const sead::Vector3f& getTranslate() const { return mTranslate; }
    void setTranslate(const sead::Vector3f& translate);

    auto getTraverseDist() const { return mTraverseDist; }
    auto getTraverseDistInt() const { return mTraverseDistInt; }

private:
    sead::TypedBitFlag<Flag0, u32> mFlags0;
    u16 mActorDataIdx = 0xffff;
    sead::TypedBitFlag<Flag, u16> mFlags;
    u8 mIdx = 0;
    u8 mNumLinksPointingToMe = 0;
    sead::TypedBitFlag<ActorFlag8, u8> mActorFlags8;
    u8 _b = 0xff;
    u16 mId = 0;
    u16 mStaticCompoundId = 0xffff;
    void* _10 = nullptr;
    void* _18 = nullptr;
    void* _20 = nullptr;
    MubinIter mMubinIter;
    act::BaseProc* mProc = nullptr;
    LinkData* mLinkData = nullptr;
    u32 mRevivalGameDataFlagHash = 0xffffffff;
    void* _50 = nullptr;
    u32 mHashId = 0;
    sead::Vector3f mTranslate;
    f32 mTraverseDist = 0.0;
    u16 mTraverseDistInt = 0;
    sead::TypedBitFlag<HardModeFlag, u8> mHardModeFlags;
};
KSYS_CHECK_SIZE_NX150(Object, 0x70);

}  // namespace ksys::map
