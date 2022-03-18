#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physShapeCast.h"

namespace ksys::phys {

QueryContactPointInfo* QueryContactPointInfo::make(sead::Heap* heap, int num_points,
                                                   const sead::SafeString& name, int a, int b) {
    auto* info = new (heap) QueryContactPointInfo(name, a, b, 0);
    info->allocPoints(heap, num_points);
    return info;
}

void QueryContactPointInfo::free(QueryContactPointInfo* info) {
    info->freePoints();
    delete info;
}

QueryContactPointInfo::~QueryContactPointInfo() = default;

// NON_MATCHING: reordering
void QueryContactPointInfo::Iterator::getHitPosition(sead::Vector3f* out,
                                                     const ShapeCast& shape_cast) const {
    float distance = getPoint()->separating_distance;
    auto start = shape_cast.getStart();
    auto end = shape_cast.getEnd();
    *out = start + (end - start) * distance;
}

sead::Vector3f QueryContactPointInfo::Iterator::getHitPosition(const ShapeCast& shape_cast) const {
    sead::Vector3f pos;
    getHitPosition(&pos, shape_cast);
    return pos;
}

void QueryContactPointInfo::Iterator::getPointPosition(sead::Vector3f* out, Point point) const {
    out->e = getPoint()->position.e;
}

sead::Vector3f QueryContactPointInfo::Iterator::getPointPosition(Point point) const {
    sead::Vector3f pos;
    getPointPosition(&pos, point);
    return pos;
}

}  // namespace ksys::phys
