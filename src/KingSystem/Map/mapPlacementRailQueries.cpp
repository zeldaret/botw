#include "KingSystem/Map/mapPlacement18.h"
#include "KingSystem/Map/mapPlacementMgr.h"
namespace ksys::map {
RailConnectablePoint* PlacementMgr::findNearestRailPoint(const sead::Vector3f& position,
                                                         int x_extent, int z_extent) {
    return mRailPlacement->findNearestRailPoint(position, x_extent, z_extent);
}
Rail* PlacementMgr::findNearestRail(const sead::SafeString& name, const sead::Vector3f& position,
                                    int x_extent, int z_extent) {
    return mRailPlacement->findNearestRail(name, position, x_extent, z_extent);
}
}  // namespace ksys::map
