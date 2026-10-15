#include "KingSystem/Map/mapPlacement18.h"
#include <cfloat>
#include <heap/seadHeap.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Map/mapRailFactoryInterfaces.h"

namespace ksys::map {

Placement18::Placement18(sead::Heap* heap)
    : mRailsByType(nullptr), mRouteRailsByCell(nullptr), mConnectableRailsByCell(nullptr) {
    if (!gRailFactory)
        createRailFactory(heap);
    mRailsByType = new (heap, 8) sead::TreeMap<u32, sead::TreeMap<u32, Rail*>*>;
    mRailsByType->allocBuffer(8, heap, 8);
    mRouteRailsByCell = new (heap, 8) sead::PtrArray<sead::PtrArray<Rail>>;
    mConnectableRailsByCell = new (heap, 8) sead::PtrArray<sead::PtrArray<Rail>>;
    mRouteRailsByCell->allocBuffer(80, heap, 8);
    mConnectableRailsByCell->allocBuffer(80, heap, 8);
    for (int i = 0; i < 80; ++i) {
        auto* routes = new (heap, 8) sead::PtrArray<Rail>;
        routes->allocBuffer(80, heap, 8);
        mRouteRailsByCell->pushBack(routes);
        auto* connectable = new (heap, 8) sead::PtrArray<Rail>;
        connectable->allocBuffer(16, heap, 8);
        mConnectableRailsByCell->pushBack(connectable);
    }
}

Placement18::~Placement18() {
    destroyRailFactory();
    for (auto* type = mRailsByType->startIterating(); type; type = mRailsByType->nextNode(type)) {
        auto* rails = type->value();
        for (auto* node = rails->startIterating(); node; node = rails->nextNode(node))
            delete node->value();
        if (rails->startIterating())
            rails->clear();
        rails->freeBuffer();
        delete rails;
    }
    if (mRailsByType->startIterating())
        mRailsByType->clear();
    mRailsByType->freeBuffer();
    delete mRailsByType;
    for (int i = 0; i < 80; ++i) {
        auto* routes = mRouteRailsByCell->at(i);
        for (auto& rail : *routes)
            delete &rail;
        routes->freeBuffer();
        delete routes;
        auto* connectable = mConnectableRailsByCell->at(i);
        for (auto& rail : *connectable)
            delete &rail;
        connectable->freeBuffer();
        delete connectable;
    }
    mRouteRailsByCell->freeBuffer();
    mConnectableRailsByCell->freeBuffer();
    delete mRouteRailsByCell;
    delete mConnectableRailsByCell;
}

RailConnectablePoint* Placement18::findNearestRailPoint(const sead::Vector3f& position,
                                                        int x_extent, int z_extent) {
    const float world_x = position.x + 5000.0f;
    const float world_z = position.z + 4000.0f;
    int cell_x = sead::Mathf::floor(world_x / 1000.0f);
    int cell_z = sead::Mathf::floor(world_z / 1000.0f);
    bool positive_x = world_x - float(cell_x * 1000) > 500.0f;
    bool positive_z = world_z - float(cell_z * 1000) > 500.0f;
    float nearest_distance = FLT_MAX;
    RailConnectablePoint* nearest = nullptr;
    const auto search_cell = [&](int x, int z) {
        if (u32(x) >= 10 || u32(z) >= 8)
            return;
        auto* rails = mConnectableRailsByCell->at(z + x * 8);
        for (auto& rail : *rails) {
            const int count = rail.getNumPoints();
            for (int i = 0; i < count; ++i) {
                auto* point = static_cast<RailConnectablePoint*>(rail.getPoint(i));
                if (!point)
                    continue;
                const auto& point_position = point->getTranslate();
                const float dx = point_position.x - position.x;
                const float dz = point_position.z - position.z;
                const float distance = dx * dx + dz * dz;
                if (distance < nearest_distance) {
                    nearest_distance = distance;
                    nearest = point;
                }
            }
        }
    };
    search_cell(cell_x, cell_z);
    int radius = 0;
    do {
        ++radius;
        cell_x += positive_x ? 1 : -1;
        search_cell(cell_x, cell_z);
        for (int i = 0; i < radius; ++i) {
            cell_z += positive_z ? 1 : -1;
            search_cell(cell_x, cell_z);
        }
        for (int i = 0; i < radius; ++i) {
            cell_x += positive_x ? -1 : 1;
            search_cell(cell_x, cell_z);
        }
        if (nearest)
            return nearest;
        positive_x = !positive_x;
        positive_z = !positive_z;
    } while (radius < x_extent || radius < z_extent);
    return nullptr;
}

Rail* Placement18::findNearestRail(const sead::SafeString& name, const sead::Vector3f& position,
                                   int x_extent, int z_extent) {
    float nearest_distance = FLT_MAX;
    Rail* nearest = nullptr;
    for (int cell = 0; cell < 80; ++cell) {
        auto* rails = mConnectableRailsByCell->at(cell);
        for (auto& rail : *rails) {
            const char* rail_name = rail.getUniqueName();
            if (!rail_name || name != sead::SafeString(rail_name))
                continue;
            const int count = rail.getNumPoints();
            for (int i = 0; i < count; ++i) {
                const auto& point = rail.getPointTranslate(i);
                const float dx = position.x - point.x;
                const float dz = position.z - point.z;
                const float distance = dx * dx + dz * dz;
                if (distance < nearest_distance) {
                    nearest_distance = distance;
                    nearest = &rail;
                }
            }
        }
    }
    return nearest;
}

}  // namespace ksys::map
