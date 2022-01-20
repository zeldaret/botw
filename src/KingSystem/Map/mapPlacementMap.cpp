#include "KingSystem/Map/mapPlacementMap.h"

namespace ksys::map {

PlacementMap::PlacementMap() {
    mInitStatus = InitStatus::None;
    mParsedNumStaticObjs = 0xFFFFFFFF;
    mStaticMapLoaded = StaticMap::None;
    mNumStaticObjs = 0xFFFFFFFF;
    mMat = sead::Matrix34f::ident;
    mDistanceToCurrentMapUnit = 0;
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

}  // namespace ksys::map
