
#include "KingSystem/Map/mapPlacementMap.h"
#include <thread/seadReadWriteLock.h>

namespace ksys::map {

PlacementMap::PlacementMap() {
    mInitStatus = InitStatus::None;
    mParsedNumStaticObjs = 0xFFFFFFFF;
    mStaticMapLoaded[0] = 0;
    mStaticMapLoaded[1] = 0;
    mNumStaticObjs = 0xFFFFFFFF;
    mMat = sead::Matrix34f::ident;
    mDistanceToCurrentMapUnit = 0;
    _0 = 0;
    mSkipLoadStaticMap = 0;
    _38c = 0xFFFFFFFF;
    mIdx = 0;
    _388 = 0;
    mCol = 0;
    mRow = 0;
    mNumRoutes = 0;
    mP18 = 0;
    mMgr = 0;
    mPa = 0;
    mDynamicGroupIdx = 0xFFFFFFFF;
    mRes[0].mStatus = HkscRes::Status::_0;
    mRes[1].mStatus = HkscRes::Status::_0;
    mRes[2].mStatus = HkscRes::Status::_0;
    mRes[3].mStatus = HkscRes::Status::_0;
}

PlacementMap::~PlacementMap() {
    mRoutes.freeBuffer();
    for (auto& r : mRes) {
        r.cleanup();
    }
}

void PlacementMap::unload() {
    sead::ReadWriteLock* lock = &mPa->lock;
    lock->writeLock();
    mPa->resetGroup(mDynamicGroupIdx);
    mDynamicGroupIdx = 0xFFFFFFFF;
    lock->writeUnlock();

    mCs.lock();
    mDynamicMubinRes.requestUnload();
    mCs.unlock();
}

phys::BodyGroup* PlacementMap::getFieldBodyGroup(u32 field_group) {
    mCs.lock();
    phys::BodyGroup* retval = nullptr;
    auto* r = mRes[0].mRes.getResource();
    if (auto* sc = sead::DynamicCast<phys::StaticCompound>(r)) {
        if (sc->fieldBodyGroupSize() > (s32)field_group) {
            retval = sc->getFieldBodyGroup(field_group);
        }
    } else {
        retval = nullptr;
    }

    mCs.unlock();
    return retval;
}

void PlacementMap::x_7(int idx, int unknown, s8 column, s8 row, const sead::SafeString& mubinPath,
                       const sead::SafeString& folderAndFile, int map_id_maybe,
                       bool skip_load_static_map) {
    _388 = unknown;  // Unknown
    mIdx = idx;
    mCol = column;
    mRow = row;
    mMubinPath.copy(mubinPath);
    mFolderAndFile.copy(folderAndFile);
    _38c = map_id_maybe; /* Index in open world map */
    mSkipLoadStaticMap = skip_load_static_map;
}

void PlacementMap::unloadHksc(s32 a2) {
    u64 k = ((u64)a2 < 4) ? a2 : 0;
    mRes[k].mRes.requestUnload();
}

}  // namespace ksys::map
