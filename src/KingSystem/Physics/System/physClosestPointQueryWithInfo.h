#pragma once

#include "KingSystem/Physics/System/physClosestPointQuery.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

// A ClosestPointQuery with an owned QueryContactPointInfo.
class ClosestPointQueryWithInfo : public ClosestPointQuery {
    SEAD_RTTI_OVERRIDE(ClosestPointQueryWithInfo, ClosestPointQuery)
public:
    enum class Status {
        _1 = 1,
        _2 = 2,
        _3 = 3,
    };

    ClosestPointQueryWithInfo(RigidBody* body, int num_points, const sead::SafeString& name, int a,
                              LowPriority low_priority);
    ~ClosestPointQueryWithInfo() override;

protected:
    Status mStatus{};
};

}  // namespace ksys::phys
