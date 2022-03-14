#pragma once

#include "KingSystem/Physics/System/physShapeCast.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class SphereRigidBody;
class SystemGroupHandler;

class ShapeCastWithInfo : public ShapeCast {
    SEAD_RTTI_OVERRIDE(ShapeCastWithInfo, ShapeCast)
public:
    ShapeCastWithInfo(RigidBody* body, int num_contact_points, Mode mode,
                      const sead::SafeString& name, LowPriority low_priority);
    ShapeCastWithInfo(RigidBody* body, QueryContactPointInfo* contact_point_info, Mode mode);

    ~ShapeCastWithInfo() override;

    bool executeQuery(WeldClosestPoints weld_closest_points) override;

protected:
    enum class Status {
        _0 = 0,
        _1 = 1,
        _2 = 2,
        _3 = 3,
    };

    void doCast(const hkpLinearCastInput& input, hkpCdPointCollector& cast_collector,
                hkpCdPointCollector* start_collector) override;

    Status mStatus = Status::_0;
};

class SphereCast : public ShapeCastWithInfo {
    SEAD_RTTI_OVERRIDE(SphereCast, ShapeCastWithInfo)
public:
    SphereCast(ContactLayer layer, GroundHit ground_hit, SystemGroupHandler* group_handler,
               int num_contact_points, Mode mode, const sead::Vector3f& from, float sphere_radius,
               const sead::SafeString& name, LowPriority low_priority);

    ~SphereCast() override;

    void setRadius(float radius);

private:
    SphereRigidBody* mSphere;
};

}  // namespace ksys::phys
