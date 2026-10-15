#include "Game/AutoPlacement/AutoPlacement.h"
#include "Game/AutoPlacement/AutoPlacementFlowInterfaces.h"
#include "Game/AutoPlacement/AutoPlacementFlowMgr.h"
#include "Game/AutoPlacement/AutoPlacementNavigationInterfaces.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapRail.h"
namespace uking::AutoPlacementFlowHandlers {
int railDistance(const evfl::QueryArg& arg) {
    ore::StringView rail_name;
    int rail_type;
    float distance;
    bool near_only;
    if (!arg.param_accessor.FindString(&rail_name, "RailName") ||
        !arg.param_accessor.FindInt(&rail_type, "RailType") ||
        !arg.param_accessor.FindFloat(&distance, "Distance") ||
        !arg.param_accessor.FindBool(&near_only, "NearOnly"))
        return -1;
    auto* manager = ksys::map::PlacementMgr::instance();
    if (!manager)
        return -1;
    const int cells = int((distance + distance) / 1000.0f) + 1;
    const int x_extent = cells >= 10 ? 10 : cells;
    const int z_extent = cells >= 8 ? 8 : cells;
    if (rail_type != 0)
        return -1;
    auto* placement = static_cast<AutoPlacementFlowRes*>(arg.actor_user_data)->placement;
    const auto& position = placement->getQueryPosition();
    const float squared_distance = distance * distance;
    ksys::map::Rail* rail;
    if (near_only) {
        auto* point = manager->findNearestRailPoint(position, x_extent, z_extent);
        if (!point)
            return 1;
        rail = point->getJunctionRail();
        if (!rail->getUniqueName())
            return 1;
        if (sead::SafeString(rail->getUniqueName()) != sead::SafeString(rail_name.data()))
            return 1;
        const auto& point_position = point->getTranslate();
        const float dx = position.x - point_position.x;
        const float dz = position.z - point_position.z;
        if (!(squared_distance > dx * dx + dz * dz))
            return 1;
    } else {
        rail = manager->findNearestRail(sead::SafeString(rail_name.data()), position, x_extent,
                                        z_extent);
        if (!rail)
            return 1;
        const int count = rail->getNumPoints();
        bool found = false;
        for (int i = 0; i < count; ++i) {
            const auto& point_position = rail->getPointTranslate(i);
            const float dx = position.x - point_position.x;
            const float dz = position.z - point_position.z;
            if (squared_distance > dx * dx + dz * dz) {
                found = true;
                break;
            }
        }
        if (!found)
            return 1;
    }
    if (placement->isSecondaryQuery())
        placement->setQueryRailName(sead::SafeString(rail->getUniqueName()));
    return 0;
}
int navMeshFace(const evfl::QueryArg& arg) {
    auto* placement = static_cast<AutoPlacementFlowRes*>(arg.actor_user_data)->placement;
    sead::Vector3f face_position;
    return ksys::ai::queryNavMeshFace(ksys::ai::gHavokAI, &face_position,
                                      placement->getQueryPosition(), 0.5f) != 23;
}
}  // namespace uking::AutoPlacementFlowHandlers
