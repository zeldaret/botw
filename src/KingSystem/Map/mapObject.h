#pragma once

#include <basis/seadTypes.h>
#include <heap/seadHeap.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actDebug.h"
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/Map/mapDebug.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class BaseProc;
class BaseProcInitializer;
class BaseProcCreateTask;
}  // namespace ksys::act

namespace ksys::map {

class ObjectLinkData;
struct ObjectLink;
struct ObjectLinkArray;
class LinkTag;

class Object {
public:
    // TODO: rename
    enum class Flag0 : u32 {
        _2 = 0x2,
        _4 = 0x4,
        _8 = 0x8,
        _10 = 0x10,
        _20 = 0x20,
        _40 = 0x40,
        _80 = 0x80,
        _100 = 0x100,
        ActorCreated = 0x200,
        _400 = 0x400,
        _800 = 0x800,
        _2000 = 0x2000,
        _4000 = 0x4000,
        _8000 = 0x8000,
        _10000 = 0x10000,
        _40000 = 0x40000,
        _80000 = 0x80000,
        _100000 = 0x100000,
        StaticCompoundInstanceEnabled = 0x200000,
        _400000 = 0x400000,
        _2000000 = 0x2000000,
        _4000000 = 0x4000000,
        _40000000 = 0x40000000,
        _80000000 = 0x80000000,
        ResetOnUnlinkFailed = _100 | _2000,
        ResetOnUnlink = _2 | _4 | _80 | _100 | ActorCreated | _400 | _2000,
        _400400 = _400 | _400000,
        _500400 = _400400 | _100000,
        _80002106 = _2 | _4 | _100 | _2000 | _80000000,
        ResetOnFreed = ResetOnUnlink | _500400 | _20 | _40 | _4000 | _2000000 | _4000000 |
                       _40000000 | _80000000,
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

    void initData(MubinIter* iter, u8 idx, u32 actor_data_idx, ActorData* data);
    void free();

    void registerBaseProc(act::BaseProc* proc);
    void setBaseProcDirect(act::BaseProc* proc);
    void onBaseProcCreated(act::BaseProc* proc);
    act::BaseProc* tryGetProc(bool force);
    void unlinkProc(bool force);

    bool getActorWithAccessor(act::ActorLinkConstDataAccess& accessor);
    act::Actor* tryGetActor(bool force);
    act::Actor* getActor();

    LinkTag* tryGetLinkTag(bool force);

    bool isEnemyOrNpcOrActiveOrMapPassive() const;
    bool isFlags8Cleared() const;
    bool isNpcOrActiveOrMapPassiveOrFlag1() const;
    bool isMapPassive(const PlacementActors* pa) const;
    bool isEnemyOrNpc(const PlacementActors* pa) const;
    bool isRevivalGameDataFlagOn() const;
    bool checkActorDataFlag(const PlacementActors* pa, ActorData::Flag flag) const;
    bool checkTraverseFlags() const;
    bool checkRevivalFlag(ActorData::Flag bit) const;

    void setRevivalFlagValueIf(ActorData::Flag bit, bool value);
    void setRevivalFlagValue(bool value);
    void setFieldATrue();

    sead::Vector3f getScale() const;
    sead::Vector3f getRotate() const;
    void setTranslate(const sead::Vector3f& translate);

    f32 getDispDistanceMultiplier() const {
        f32 mult = 1.0;

        if (act::ActorDebug::instance() != nullptr)
            mult = act::ActorDebug::instance()->mDispDistanceMultiplier;

        return mult;
    }

    void getTraversePosAndLoadDistance(sead::Vector3f* traverse_pos, f32* load_dist) const;
    f32 getDispDistance(const PlacementActors* pa, bool get_diameter, bool ignore_radius) const;
    f32 getDispDistance(const ActorData* data, bool get_diameter, u32 unused,
                        bool ignore_radius) const;
    f32 getDispDistance(bool get_diameter = false, bool ignore_radius = false) const;
    f32 getTraverseDist(const ActorData* data, bool get_diameter, u32 unused,
                        bool ignore_radius) const;
    f32 getTraverseDistForLOD() const;

    const char* getUnitConfigName() const;
    const char* getUnitConfigNameFromByaml() const;
    void getUniqueName(const char** out) const;

    Object* findPlacementLODLinkObject(const PlacementActors* unused) const;
    Object* findPlacementLODLinkObject() const;

    const char* getHashIdStringDebug() const;
    const char* getHashIdStringDebug_0() const;

    bool x_18() const;
    bool x_20() const;
    s32 x_22() const;

    bool hasGenGroup() const;
    void spawnGenGroupActorsIfNeeded(Object* obj);

    void* getRails() const;
    void* getRails_0() const;
    bool setupTargetLinks(Object* src, ObjectLink* link, sead::Heap* heap);
    bool allocLinkData(sead::Heap* heap);
    void incrementLinkNum();
    void decrementLinkNum();
    bool checkCreateOrDeleteLinkObjRevival() const;

    bool shouldSkipSpawn() const;
    bool shouldSkipSpawn_(bool x) const;

    // TODO:
    void initRevivalGameDataFlagAndMiscFlags(ActorData* data, bool zero);
    f32 getLoadDistance(bool get_diameter) const;
    Object* findSrcLODLinkObject() const;

    const auto& getFlags0() const { return mFlags0; }
    void setFlags0(Flag0 bit) { mFlags0.set(bit); }
    void resetFlags0(Flag0 bit) { mFlags0.reset(bit); }
    const auto& getFlags() const { return mFlags; }
    const auto& getActorFlags8() const { return mActorFlags8; }
    const auto& getHardModeFlags() const { return mHardModeFlags; }

    auto getActorDataIdx() const { return mActorDataIdx; }
    auto getIdx() const { return mIdx; }
    auto getId() const { return mId; }
    auto getStaticCompoundActorId() const { return mStaticCompoundActorId; }
    void setStaticCompoundActorId(s16 id) { mStaticCompoundActorId = id; }

    const ActorData& getActorData() const {
        return PlacementMgr::instance()->mPlacementActors->mActorData[mActorDataIdx];
    }

    u8 getNumLinksPointingToMe() const { return mNumLinksPointingToMe; }

    const MubinIter& getMubinIter() const { return mMubinIter; }
    act::BaseProc* getProc() const { return mProc; }
    ObjectLinkData* getLinkData() const { return mLinkData; }

    gdt::FlagHandle getRevivalGameDataFlagHash() const { return mRevivalGameDataFlagHash; }
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
    s16 mStaticCompoundActorId = -1;
    void* _10 = nullptr;
    void* _18 = nullptr;
    void* _20 = nullptr;
    MubinIter mMubinIter;
    act::BaseProc* mProc = nullptr;
    ObjectLinkData* mLinkData = nullptr;
    gdt::FlagHandle mRevivalGameDataFlagHash = gdt::InvalidHandle;
    void* _50 = nullptr;
    u32 mHashId = 0;
    sead::Vector3f mTranslate;
    f32 mTraverseDist = 0.0;
    u16 mTraverseDistInt = 0;
    sead::TypedBitFlag<HardModeFlag, u8> mHardModeFlags;
};
KSYS_CHECK_SIZE_NX150(Object, 0x70);

}  // namespace ksys::map
