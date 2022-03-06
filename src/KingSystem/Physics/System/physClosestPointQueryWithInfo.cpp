#include "KingSystem/Physics/System/physClosestPointQueryWithInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

ClosestPointQueryWithInfo::ClosestPointQueryWithInfo(RigidBody* body, int num_points,
                                                     const sead::SafeString& name, int a,
                                                     LowPriority low_priority)
    : ClosestPointQuery(body, nullptr) {
    mStatus = Status::_1;
    auto* heap = System::instance()->getPhysicsTempHeap(low_priority);
    mContactPointInfo = QueryContactPointInfo::make(heap, num_points, name, a, 0);
}

ClosestPointQueryWithInfo::~ClosestPointQueryWithInfo() {
    if (mStatus == Status::_1 || mStatus == Status::_3) {
        QueryContactPointInfo::free(mContactPointInfo);
    }
}

}  // namespace ksys::phys
