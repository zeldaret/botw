#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Map/mapPlacementMap.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

class MapProperties;
class Placement18;
class FarActorMerge;

class PlacementMap;

/* NOT WORKING */
class PlacementMapArray {
public:
    PlacementMapArray() = default;
    ~PlacementMapArray() = default;

    sead::PtrArray<PlacementMap> mMaps;
    sead::PtrArray<PlacementMap> mPtrs;
    PlacementActors* mPa;
    s64 _28;
    res::Handle mRes;
    Placement18* mP18;
    s32 _88;
    s32 _8c;
    void* _90;
};
KSYS_CHECK_SIZE_NX150(PlacementMapArray, 0x98);

/* NOT WORKING */
class PlacementMapMgr {
    SEAD_SINGLETON_DISPOSER(PlacementMapMgr)

public:
    PlacementMapMgr() = default;
    ~PlacementMapMgr() = default;

    void junk();  // Here to make compiler include MapPlacement - REMOVE

    s32 mNumMaps;
    s32 _4;
    PlacementMap* mMaps;
    MapProperties* mMapProps;
    s32 _18;
    s32 _1c;
    PlacementMapArray mMapArray;
    FarActorMerge* mFarActorMerge;
    s32 mNeedLoadDynMap;
    s32 mNeedLoadDynMapPhysics;
    bool mIsShrineOrDivineBeast;
    bool mIsShrine;
    // char pad[6];
};
/* Size - D0 ? */
KSYS_CHECK_SIZE_NX150(PlacementMapMgr, 0xF0);

}  // namespace ksys::map
