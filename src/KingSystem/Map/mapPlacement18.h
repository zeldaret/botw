#pragma once
#include <container/seadPtrArray.h>
#include <container/seadTreeMap.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"
namespace ksys::map {
class Rail;
class RailConnectablePoint;
class Placement18 {
public:
    explicit Placement18(sead::Heap* heap);
    ~Placement18();
    RailConnectablePoint* findNearestRailPoint(const sead::Vector3f& position, int x_extent,
                                               int z_extent);
    Rail* findNearestRail(const sead::SafeString& name, const sead::Vector3f& position,
                          int x_extent, int z_extent);

private:
    sead::TreeMap<u32, sead::TreeMap<u32, Rail*>*>* mRailsByType;
    sead::PtrArray<sead::PtrArray<Rail>>* mRouteRailsByCell;
    sead::PtrArray<sead::PtrArray<Rail>>* mConnectableRailsByCell;
};
KSYS_CHECK_SIZE_NX150(Placement18, 0x18);
}  // namespace ksys::map
