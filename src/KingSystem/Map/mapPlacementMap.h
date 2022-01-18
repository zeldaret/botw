#pragma once

#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <heap/seadExpHeap.h>
#include <math/seadMatrix.h>
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompound.h"
#include "KingSystem/Resource/resHandle.h"

namespace ksys::map {

class PlacementMapMgr; /* See Below */
class MapProperties;
class Placement18;
class FarActorMerge;

class PlacementMapHkscRes {
    enum {
        Status_2 = 2,  // Call cleanupHkscMaybe(), if ok, set to 3
        Status_3 = 3,
        Status_4 = 4,  // Call staticCompoundStuff, if ok, set to 5
        Status_5 = 5,
    };

public:
    PlacementMapHkscRes() = default;
    ~PlacementMapHkscRes() = default;

    ksys::res::Handle res;
    s32 statusMaybe;
    bool _54;
    bool _55;
    bool _56;
    bool _57;

    void cleanup() {
        auto r = res.getResource();
        if (auto ptr = sead::DynamicCast<ksys::phys::StaticCompound>(r)) {
            if (ptr->calledFromMapDtor()) {
                ptr->cleanUp();
            }
        }
    }
};
KSYS_CHECK_SIZE_NX150(PlacementMapHkscRes, 0x58);

class PlacementMap {
    enum { StaticMap_None = 0, StaticMap_Loaded = 1 << 0, StaticMap_Parsed = 1 << 8 };

public:
    __attribute__((noinline)) PlacementMap() {
        initStatus = PlacementMap::InitStatus_None;
        parsedNumStaticObjs = 0xFFFFFFFF;
        staticMapLoaded = StaticMap_None;
        numStaticObjs = 0xFFFFFFFF;
        mat = sead::Matrix34f::ident;
        distanceToCurrentMapUnit = 0;
        skipLoadStaticMap = 0;
        _38c = 0xFFFFFFFF;
        idx = 0;
        _388 = 0;
        col = 0;
        row = 0;
        numRoutes = 0;
        p18 = 0;
        mgr = 0;
        pa = 0;
        dynamicGroupIdx = 0xFFFFFFFF;
        res[0].statusMaybe = 0;
        res[1].statusMaybe = 0;
        res[2].statusMaybe = 0;
        res[3].statusMaybe = 0;
    };

    ~PlacementMap() {
        routes.freeBuffer();
        for (auto& r : res) {
            r.cleanup();
        }
    }

    s32 loadStaticMap_(u8 load);
    void doLoadStaticMap_(bool load);

    bool parseStaticMap_(sead::ExpHeap* heap, u8* data);
    void parseMap_(sead::ExpHeap* heap, u8* data, int group, u32 idx);

    bool loadDynamicMap();

    s32 parseDynamicMap();

    void resetDynamic();
    void unload();
    void unloadStaticMubin();
    s32 x_6();
    void x_5();
    s64 traverseStuff(sead::Vector3f vec, map::PlacementActors* pa, int a4);

    phys::BodyGroup* getFieldBodyGroup(u32 a2);
    void cleanupPhysics();
    bool loadStaticCompound(int wl_0, bool a3, bool a4);
    s32 x_2(s32 a2);
    void x(int a2, map::Object* obj);
    void unloadHksc(s32 a2);
    s32 x_4(s64 a2);
    s32 x_1(s64 a2);
    bool staticCompoundStuff(s32 scId, bool cleanup);
    s64 cleanHkscMaybe(s32 a2);
    bool sub_7100D43F18(sead::Vector3f* pos);
    void doDisableObjStaticCompound(map::Object* obj, bool disable);
    void x_9();

    void x_7(int idx, int a3, char column, char row, sead::SafeString* mubinPath,
             sead::SafeString* folderAndFile, int a8, bool a9);

    enum {
        InitStatus_None = 0,
        InitStatus_StaticLoaded = 1,
        InitStatus_DynamicLoadStarted = 2,
        InitStatus_DynamicLoaded = 3,
        InitStatus_4 = 4,
        InitStatus_5 = 5,  // x_9 takes initStatus from 4 to 5 in pmm->updateHkscLoadStatuesMaybe()

    };

    u16 skipLoadStaticMap;
    u16 staticMapLoaded;
    u16 _04;
    s16 _06;
    sead::FixedSafeString<128> mubinPath;         // 008
    sead::FixedSafeString<128> folderAndFile;     // 0a0
    u32 idx;                                      //
    sead::SafeArray<PlacementMapHkscRes, 4> res;  // 140
    ksys::res::Handle staticMubinRes;             // 2a0
    ksys::res::Handle dynamicMubinRes;            // 2f0
    s32 dynamicGroupIdx;                          // 340
    s32 parsedNumStaticObjs;                      // 344
    s32 numStaticObjs;                            // 348
    u32 initStatus;                               // 34c
    s8 col;                                       // 350
    s8 row;                                       // 351
    u16 field_352;                                // 352
    sead::Matrix34f mat;                          // 354
    s32 distanceToCurrentMapUnit;                 // 384
    u32 _388;                                     // 388 check x_7() called ....
    u32 _38c;                                     // 38c ... from MapMgr::ctor (a8)
    ksys::map::PlacementActors* pa;               // 390
    ksys::map::PlacementMapMgr* mgr;              // 398
    void* p18;                                    // 3a0
    sead::Buffer<void*> routes;                   // 3a8 Raw Object Data
    s32 numRoutes;                                // 3b8
    s32 gap_38c;                                  // 3bc
    sead::CriticalSection cs;                     // 3c0
};

KSYS_CHECK_SIZE_NX150(PlacementMap, 0x400);

/* NOT WORKING */
class PlacementMapMgrMapArray {
public:
    PlacementMapMgrMapArray() = default;
    ~PlacementMapMgrMapArray() = default;

    sead::PtrArray<PlacementMap> maps; /* 0x00 */
    sead::PtrArray<PlacementMap> ptrs; /* 0x10 */
    map::PlacementActors* pa;          /* 0x20 */
    s64 _28;                           /* 0x28 */
    ksys::res::Handle res;             /* 0x30 */
    Placement18* p18;                  /* 0x80 */
    s32 _88;                           /* 0x88 */
    s32 _8c;                           /* 0x8c */
    void* _90;                         /* 0x90 */
};
KSYS_CHECK_SIZE_NX150(PlacementMapMgrMapArray, 0x98);

/* NOT WORKING */
class PlacementMapMgr {
    SEAD_SINGLETON_DISPOSER(PlacementMapMgr)
public:
    PlacementMapMgr() = default;
    ~PlacementMapMgr() = default;

    void junk();  // Here to make compiler include MapPlacement - REMOVE

    s32 numMaps;                                 /* 0x00 */
    s32 _4;                                      /* 0x04 */
    ksys::map::PlacementMap* maps;               /* 0x08 */
    ksys::map::MapProperties* mapProps;          /* 0x10 */
    s32 _18;                                     /* 0x18 */
    s32 _1c;                                     /* 0x1c */
    ksys::map::PlacementMapMgrMapArray mapArray; /* 0x20 */
    ksys::map::FarActorMerge* farActorMerge;     /* 0xB8 */
    s32 needLoadDynMap;                          /* 0xC0 */
    s32 needLoadDynMapPhysics;                   /* 0xC4 */
    char isShrineOrDivineBeast;                  /* 0xC8 */
    char isShrine;                               /* 0xC9 */
    char _ca[6];                                 /* 0xCA */
};
/* Size - D0 ? */
KSYS_CHECK_SIZE_NX150(PlacementMapMgr, 0xF0);

}  // namespace ksys::map
