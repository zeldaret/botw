#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <prim/seadTypedLongBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

// TODO: rename
enum class ActorFlag8 {
    EnemyOrNpcOrActiveOrAreaOrAirWall = 0x2,
    MapPassiveOrFlag1 = 0x4,
};

class ActorData {
public:
    enum class Flag {
        MapPassive = 0,
        _1 = 1,
        _2 = 2,
        _3 = 3,
        _4 = 4,
        _5 = 5,
        _6 = 6,
        _7 = 7,
        MapConstActive = 8,
        TraverseDist200 = 9,
        TraverseDist400 = 10,
        TraverseDist800 = 11,
        TraverseDistReset = 12,
        TraverseDist2000 = 13,
        TraverseDist4000 = 14,
        _15 = 15,
        _16 = 16,
        RevivalEnable = 17,
        RevivalForUsed = 18,
        RevivalForDrop = 19,
        RevivalRandom = 20,
        RevivalBloodyMoon = 21,
        RevivalUnderGodTimeOrNoneForUsed = 22,
        EnableRemainsScene = 23,
        _24 = 24,
        EnemyOrNpc_DisableFlashback = 25,
        _26 = 26,
        LimitYDiff = 27,
        IsGrassCut = 28,
        HasFar = 29,
        Fairy = 30,
        UnderGodForest = 31,

        EnemyOrNpc = 32,
        MapConstPassive = 33,
        RandomCreateNotRain = 34,
        _35 = 35,
        MessageDialogViewBoard = 36,
        _37 = 37,
        NpcOrNonGanonAndNonGuardianEnemy = 38,
        IgnoreBoundingAtAreaCulling = 39,
        _40 = 40,
        EnemyHuge = 41,
        Enemy = 42,
        _43 = 43,
        EnemyLookOrGrassCutTagOrFirePillarOrDgnWater = 44,
        _45 = 45,
        MapPassiveOrFlag1 = 46,
        _47 = 47,
        _48 = 48,
        SheikSensorTargetDeadOrAlive = 49,
        Dragon = 50,
        TreeOrBush = 51,
        GuardianC = 52,
        _53 = 53,
        HasStopTimerFlag = 54,
        AllRadarOrZukanActor = 55,
        NoCreateForStackLink = 56,
        OnLowTree = 57,
        _58 = 58,
        _59 = 59,
        _60 = 60,
        _61 = 61,
        _62 = 62,
        _63 = 63,
    };

    sead::TypedLongBitFlag<64, Flag, sead::Atomic<u32>> mFlags;
    sead::TypedBitFlag<ActorFlag8, u8> mActorFlags8;
    u8 TEMP[0x13F];
    sead::FixedSafeString<64> mActorName;
};
KSYS_CHECK_SIZE_NX150(ActorData, 0x1A0);

// FIXME: move this to another header and rename
// FIXME: incomplete
class PlacementStruct1 {
public:
    sead::BitFlag16 mFlags;
    bool mIsOneHitChallengeActive;
};

class PlacementActors {
public:
    u8 _0[0xe0 - 0x0];
    PlacementStruct1* mStruct1;
    u8 _e8[0x538 - 0xe8];
    sead::SafeArray<ActorData, 6000> mActorData;
    u8 _261b38[0x2a80d0 - 0x261b38];
};
KSYS_CHECK_SIZE_NX150(PlacementActors, 0x2A80D0);

class PlacementMgr {
    SEAD_SINGLETON_DISPOSER(PlacementMgr)
    PlacementMgr();
    virtual ~PlacementMgr();

public:
    enum class MgrFlag {
        _1000000 = 0x1000000,
    };

    u8 TEMP1[0x1C8];
    PlacementActors* mPlacementActors;
    u8 TEMP2[0x48C];
    sead::TypedBitFlag<MgrFlag, sead::Atomic<u32>> mFlags;
    u8 TEMP3[0x190];
};
KSYS_CHECK_SIZE_NX150(PlacementMgr, 0x818);

}  // namespace ksys::map
