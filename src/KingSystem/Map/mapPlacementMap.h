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
    struct HkscRes {
    public:
        enum class Status : int {
            _0 = 0,
            _1 = 1,
            _2 = 2,  // Call cleanupHkscMaybe(), if ok, set to 3
            _3 = 3,
            _4 = 4,  // Call staticCompoundStuff, if ok, set to 5
            _5 = 5,
        };

        HkscRes() = default;
        ~HkscRes() = default;

        void cleanup() {
            auto* r = mRes.getResource();
            if (auto sc = sead::DynamicCast<phys::StaticCompound>(r)) {
                if (sc->calledFromMapDtor()) {
                    sc->cleanUp();
                }
            }
        }

        res::Handle mRes;
        Status mStatus;
    };
    KSYS_CHECK_SIZE_NX150(HkscRes, 0x58);

    enum class StaticMap : u16 { None = 0, Loaded = 1 << 0, Parsed = 1 << 8 };
    enum class InitStatus : int {
        None = 0,
        StaticLoaded = 1,
        DynamicLoadStarted = 2,
        DynamicLoaded = 3,
        _4 = 4,
        _5 = 5,  // x_9 takes initStatus from 4 to 5 in pmm->updateHkscLoadStatuesMaybe()
    };
    KSYS_CHECK_SIZE_NX150(InitStatus, 4);

public:
    PlacementMap();
    ~PlacementMap();

private:
    int loadStaticMap_(bool load);
    void doLoadStaticMap_(bool load);

    bool parseStaticMap_(sead::Heap* heap, u8* data);
    void parseMap_(sead::Heap* heap, u8* data, int group, u32 idx);

    bool loadDynamicMap();

    int parseDynamicMap();

    void resetDynamic();
    void unload();
    void unloadStaticMubin();
    int x_6();
    void x_5();
    int traverseStuff(sead::Vector3f* vec, PlacementActors* pa, int id);

    phys::BodyGroup* getFieldBodyGroup(u32 field_body_group_index);
    void cleanupPhysics();
    bool loadStaticCompound(int index, bool is_auto_gen_mu, bool load_maybe);
    int x_2(int id);
    void x(int id, Object* obj);
    void unloadHksc(int id);
    int x_4(int id);
    int x_1(int id);
    bool staticCompoundStuff(int sc_id, bool cleanup);
    int cleanHkscMaybe(int id);
    bool sub_7100D43F18(const sead::Vector3f& pos);
    void doDisableObjStaticCompound(Object* obj, bool disable);
    void x_9();

    void x_7(int idx, int unknown, char column, char row, const sead::SafeString& mubinPath,
             const sead::SafeString& folderAndFile, int map_id_maybe, bool skip_load_static_map);

    u16 mSkipLoadStaticMap;
    StaticMap mStaticMapLoaded;
    u16 _04;
    s16 _06;
    sead::FixedSafeString<128> mMubinPath;
    sead::FixedSafeString<128> mFolderAndFile;
    u32 mIdx;
    sead::SafeArray<HkscRes, 4> mRes;
    res::Handle mStaticMubinRes;
    res::Handle mDynamicMubinRes;
    int mDynamicGroupIdx;
    int mParsedNumStaticObjs;
    int mNumStaticObjs;
    InitStatus mInitStatus;
    s8 mCol;
    s8 mRow;
    u16 _352;
    sead::Matrix34f mMat;
    int mDistanceToCurrentMapUnit;
    u32 _388;  // 388 check x_7() called ....
    u32 _38c;  // 38c ... from MapMgr::ctor (a8)
    PlacementActors* mPa;
    PlacementMapMgr* mMgr;
    void* mP18;
    sead::Buffer<void*> mRoutes;
    int mNumRoutes;
    int gap_38c;
    sead::CriticalSection mCs;
};

KSYS_CHECK_SIZE_NX150(PlacementMap, 0x400);

}  // namespace ksys::map
