#pragma once

#include <basis/seadTypes.h>
#include <heap/seadHeap.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actDebug.h"
#include "KingSystem/Map/mapDebug.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class BaseProc;
}

namespace ksys::map {

class Object;

class ObjectLinkData;
struct ObjectLink;
struct ObjectLinkArray;

class LinkTag;

// FIXME: incomplete
class Object {
public:
    // TODO: rename
    enum class Flag0 : u32 {
        _2 = 0x2,
        _4 = 0x4,
        _8 = 0x8,
        _10 = 0x10,
        _20 = 0x20,
        _80 = 0x80,
        _8000 = 0x8000,
        _40000 = 0x40000,
        _80000 = 0x80000,
        Freed = 0xC65067E6,
        _80000000 = 0x80000000,
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

    void free();

    void onBaseProcCreated(act::BaseProc* proc);

    bool getActorWithAccessor(act::ActorLinkConstDataAccess& accessor) const;
    act::Actor* getActor() const;
    void registerBaseProc(act::BaseProc* proc);
    void setBaseProcDirect(act::BaseProc* proc);

    bool isEnemyOrNpcOrActiveOrMapPassive() const;
    bool isFlags8Cleared() const;
    bool isNpcOrActiveOrMapPassiveOrFlag1() const;
    bool isMapPassive(const PlacementActors* pa) const;
    bool checkActorDataFlag(const PlacementActors* pa, ActorData::Flag flag) const;
    bool isEnemyOrNpc(const PlacementActors* pa) const;

    f32 getDispDistanceMultiplier() const {
        f32 mult = 1.0;

        if (act::ActorDebug::instance() != nullptr)
            mult = act::ActorDebug::instance()->mDispDistanceMultiplier;

        return mult;
    }

    f32 getDispDistance(const PlacementActors* pa, bool get_diameter, bool ignore_radius) const;
    f32 getDispDistance(const ActorData* data, bool get_diameter, u32 unused,
                        bool ignore_radius) const;
    f32 getDispDistance(bool get_diameter = false, bool ignore_radius = false) const;

    f32 getTraverseDist(const ActorData* data, bool get_diameter, u32 unused,
                        bool ignore_radius) const;
    f32 getTraverseDistForLOD() const;
    sead::Vector3f getScale() const;

    const char* getUnitConfigName() const;
    const char* getUnitConfigNameFromByaml() const;

    Object* findPlacementLODLinkObject(const PlacementActors* unused) const;
    Object* findPlacementLODLinkObject() const;

    const char* getHashIdStringDebug() const;
    const char* getHashIdStringDebug_0() const;

    void* getRails() const;
    void* getRails_0() const;
    bool allocLinkData(sead::Heap* heap);
    bool hasGenGroup() const;
    void incrementLinkNum();
    void decrementLinkNum();

    sead::Vector3f getRotate() const;
    void getTraversePosAndLoadDistance(sead::Vector3f* traverse_pos, f32* load_dist) const;
    void getUniqueName(const char** out) const;
    void setTranslate(const sead::Vector3f& translate);

    // TODO:
    void initData(MubinIter* iter, u8 idx, u32 actor_data_idx, ActorData* data);
    void initRevivalGameDataFlagAndMiscFlags(ActorData* data, bool zero);
    act::BaseProc* getActor_0(bool a1) const;
    LinkTag* x_10(bool a1) const;
    f32 getLoadDistance(bool get_diameter) const;
    Object* findSrcLODLinkObject() const;
    bool isRevivalGameDataFlagOn() const;

    const auto& getFlags0() const { return mFlags0; }
    const auto& getFlags() const { return mFlags; }
    const auto& getActorFlags8() const { return mActorFlags8; }
    const auto& getHardModeFlags() const { return mHardModeFlags; }

    auto getActorDataIdx() const { return mActorDataIdx; }
    auto getIdx() const { return mIdx; }
    auto getId() const { return mId; }
    auto getStaticCompoundId() const { return mStaticCompoundId; }

    const ActorData& getActorData() const {
        return PlacementMgr::instance()->mPlacementActors->mActorData[mActorDataIdx];
    }

    u8 getNumLinksPointingToMe() const { return mNumLinksPointingToMe; }

    const MubinIter& getMubinIter() const { return mMubinIter; }
    act::BaseProc* getProc() const { return mProc; }
    ObjectLinkData* getLinkData() const { return mLinkData; }

    u32 getRevivalGameDataFlagHash() const { return mRevivalGameDataFlagHash; }
    u32 getHashId() const { return mHashId; }

    const sead::Vector3f& getTranslate() const { return mTranslate; }

    auto getTraverseDistInt() const { return mTraverseDistInt; }

private:
    sead::TypedBitFlag<Flag0, sead::Atomic<u32>> mFlags0;
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
    ObjectLinkData* mLinkData = nullptr;
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
