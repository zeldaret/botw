#include "KingSystem/Physics/System/physQueryContactPointInfo.h"

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

}  // namespace ksys::phys
