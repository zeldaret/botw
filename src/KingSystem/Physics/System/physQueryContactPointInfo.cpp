#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physContactMgr.h"

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

void QueryContactPointInfo::Iterator::getPointPosition(sead::Vector3f* out, Point point) const {
    out->e = getPoint()->position.e;
}

sead::Vector3f QueryContactPointInfo::Iterator::getPointPosition(Point point) const {
    sead::Vector3f pos;
    getPointPosition(&pos, point);
    return pos;
}

}  // namespace ksys::phys
