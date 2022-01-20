#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <heap/seadHeap.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementMapMgr.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompound.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

class PlacementMapMgr;

class PlacementMap {
public:
    struct HkscRes {
        enum class Status {
            _0 = 0,
            _1 = 1,
            _2 = 2,  // Call cleanupHkscMaybe(), if ok, set to 3
            _3 = 3,
            _4 = 4,  // Call staticCompoundStuff, if ok, set to 5
            _5 = 5,
        };

        HkscRes() = default;
        ~HkscRes() = default;

        res::Handle mRes;
        Status mStatus;
        // bool _pad[4];

        void cleanup() {
            auto* r = mRes.getResource();
            if (auto sc = sead::DynamicCast<phys::StaticCompound>(r)) {
                if (sc->calledFromMapDtor()) {
                    sc->cleanUp();
                }
            }
        }
    };
    KSYS_CHECK_SIZE_NX150(HkscRes, 0x58);

    // This enum is used on a u16. enum classses are 32 bit
    enum { StaticMap_None = 0, StaticMap_Loaded = 1 << 0, StaticMap_Parsed = 1 << 8 };
    enum class InitStatus {
        None = 0,
        StaticLoaded = 1,
        DynamicLoadStarted = 2,
        DynamicLoaded = 3,
        _4 = 4,
        _5 = 5,  // x_9 takes initStatus from 4 to 5 in pmm->updateHkscLoadStatuesMaybe()
    };
    KSYS_CHECK_SIZE_NX150(InitStatus, 4);

    PlacementMap();
    ~PlacementMap();

    s32 loadStaticMap_(bool load);
    void doLoadStaticMap_(bool load);

    bool parseStaticMap_(sead::Heap* heap, u8* data);
    void parseMap_(sead::Heap* heap, u8* data, int group, u32 idx);

    bool loadDynamicMap();

    s32 parseDynamicMap();

    void resetDynamic();
    void unload();
    void unloadStaticMubin();
    s32 x_6();
    void x_5();
    s64 traverseStuff(sead::Vector3f* vec, PlacementActors* pa, int id);

    phys::BodyGroup* getFieldBodyGroup(u32 field_body_group_id);
    void cleanupPhysics();
    bool loadStaticCompound(int id, bool is_auto_gen_mu, bool load_maybe);
    s32 x_2(s32 id);
    void x(int id, Object* obj);
    void unloadHksc(s32 id);
    s32 x_4(s64 id);
    s32 x_1(s64 id);
    bool staticCompoundStuff(s32 sc_id, bool cleanup);
    s64 cleanHkscMaybe(s32 id);
    bool sub_7100D43F18(sead::Vector3f& pos);
    void doDisableObjStaticCompound(Object* obj, bool disable);
    void x_9();

    void x_7(int idx, int unknown, char column, char row, sead::SafeString* mubinPath,
             sead::SafeString* folderAndFile, int map_id_maybe, bool skip_load_static_map);

    u16 mSkipLoadStaticMap;
    u16 mStaticMapLoaded;
    u16 _04;
    s16 _06;
    sead::FixedSafeString<128> mMubinPath;
    sead::FixedSafeString<128> mFolderAndFile;
    u32 mIdx;
    sead::SafeArray<HkscRes, 4> mRes;
    res::Handle mStaticMubinRes;
    res::Handle mDynamicMubinRes;
    s32 mDynamicGroupIdx;
    s32 mParsedNumStaticObjs;
    s32 mNumStaticObjs;
    InitStatus mInitStatus;
    s8 mCol;
    s8 mRow;
    u16 _352;
    sead::Matrix34f mMat;
    s32 mDistanceToCurrentMapUnit;
    u32 _388;  // 388 check x_7() called ....
    u32 _38c;  // 38c ... from MapMgr::ctor (a8)
    PlacementActors* mPa;
    PlacementMapMgr* mMgr;
    void* mP18;
    sead::Buffer<void*> mRoutes;
    s32 mNumRoutes;
    s32 gap_38c;
    sead::CriticalSection mCs;
};

KSYS_CHECK_SIZE_NX150(PlacementMap, 0x400);

}  // namespace ksys::map
