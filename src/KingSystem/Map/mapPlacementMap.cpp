#include "KingSystem/Map/mapPlacementMap.h"

namespace ksys::map {

SEAD_SINGLETON_DISPOSER_IMPL(PlacementMapMgr)

void PlacementMapMgr::junk() {
    /*  Here to force the compiler to include PlacementMap */
    PlacementMap x;
    auto y = new PlacementMap;
    (void)(x);
    (void)(y);
}

}  // namespace ksys::map
