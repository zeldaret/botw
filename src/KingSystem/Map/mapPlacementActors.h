#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <prim/seadTypedLongBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadReadWriteLock.h>
#include "KingSystem/Map/mapPlacementMap.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

class Object;
class PlacementMap;
class PlacementAreaMgr;

// TODO: rename
enum class ActorFlag8 {
    MapPassive = 0x1,
    EnemyOrNpcOrActiveOrAreaOrAirWall = 0x2,
    UndispCutOrPreActorXLinkOrChemical = 0x4,
    _8 = 0x8,
    CanGetPouch = 0x10,
    HasCreateOrDeleteLink = 0x20,
    DragonDropItemTarget = 0x40,
    TreeOrBush = 0x80,
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

class PlacementActors {
public:
    u32 getNumStaticObjs() const;
    Object* getStaticObj_2(s32 idx) const;
    bool sub_7100D524B4() const;
    void x_9();
    Object* resetGroup(int group_idx);
    int getNumObjs(int group_idx) const;
    Object* getObj(int group_idx, int object_idx);
    Object* getStaticObj_0(int object_idx);
    u32 allocGroupForDynamicMap(PlacementMap* pmap);

    u8 _0[0x28 - 0x0];
    sead::ReadWriteLock mLock;
    PlacementAreaMgr* mStruct1;
    u8 _e8[0x538 - 0xe8];
    sead::SafeArray<ActorData, 6000> mActorData;
    u8 _261b38[0x2a8058 - 0x261b38];
    u32 mActorDataMapSize;
    u8 _2a805c[0x2a80d0 - 0x2a805c];
};
KSYS_CHECK_SIZE_NX150(PlacementActors, 0x2A80D0);

}  // namespace ksys::map
