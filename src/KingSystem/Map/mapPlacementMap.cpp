
#include "KingSystem/Map/mapPlacementMap.h"
#include <prim/seadScopedLock.h>
#include <thread/seadReadWriteLock.h>

namespace ksys::map {

PlacementMap::PlacementMap() {
    mInitStatus = InitStatus::None;
    mParsedNumStaticObjs = 0xFFFFFFFF;
    mStaticMapLoaded = false;
    mStaticMapParsed = false;
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
    sead::ReadWriteLock* lock = &mPa->mLock;
    lock->writeLock();
    mPa->resetGroup(mDynamicGroupIdx);
    mDynamicGroupIdx = 0xFFFFFFFF;
    lock->writeUnlock();

    mCs.lock();
    mDynamicMubinRes.requestUnload();
    mCs.unlock();
}

phys::BodyGroup* PlacementMap::getFieldBodyGroup(int field_group_idx) {
    const auto lock = sead::makeScopedLock(mCs);

    auto* r = mRes[0].mRes.getResource();
    if (auto* sc = sead::DynamicCast<phys::StaticCompound>(r)) {
        if (field_group_idx < sc->getNumFieldBodyGroups()) {
            return sc->getFieldBodyGroup(field_group_idx);
        }
    }
    return nullptr;
}

void PlacementMap::x_7(int idx, int unknown, s8 column, s8 row, const sead::SafeString& mubin_path,
                       const sead::SafeString& folder_and_file, int map_id_maybe,
                       bool skip_load_static_map) {
    _388 = unknown;
    mIdx = idx;
    mCol = column;
    mRow = row;
    mMubinPath.copy(mubin_path);
    mFolderAndFile.copy(folder_and_file);
    _38c = map_id_maybe;  // Index in open world map
    mSkipLoadStaticMap = skip_load_static_map;
}

void PlacementMap::unloadHksc(int hksc_idx) {
    mRes[hksc_idx].mRes.requestUnload();
}

}  // namespace ksys::map
