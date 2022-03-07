#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/System/physClosestPointQuery.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

struct RigidBodyInstanceParam;

/// A ClosestPointQuery with an owned QueryContactPointInfo.
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

/// A closest point query using a sphere rigid body.
class SphereBasedClosestPointQuery : public ClosestPointQueryWithInfo {
    SEAD_RTTI_OVERRIDE(SphereBasedClosestPointQuery, ClosestPointQueryWithInfo)
public:
    SphereBasedClosestPointQuery(const sead::Vector3f& position, float sphere_radius,
                                 ContactLayer layer, GroundHit ground_hit,
                                 SystemGroupHandler* group_handler, int num_points,
                                 const sead::SafeString& name, int a, LowPriority low_priority);

    SphereBasedClosestPointQuery(const sead::Vector3f& position, float sphere_radius,
                                 ContactLayer layer, const LayerMaskBuilder& layer_mask_builder,
                                 int num_points, const sead::SafeString& name, int a,
                                 LowPriority low_priority);

    SphereBasedClosestPointQuery(const sead::Vector3f& position, float sphere_radius,
                                 const SensorCollisionMask& mask, SystemGroupHandler* group_handler,
                                 int num_points, const sead::SafeString& name, int a,
                                 LowPriority low_priority);

    // TODO: figure out if this is really only used with spheres
    SphereBasedClosestPointQuery(RigidBody* sphere, const sead::Vector3f& position, int num_points,
                                 const sead::SafeString& name, int a, LowPriority low_priority);

    ~SphereBasedClosestPointQuery() override;

protected:
    void makeAndSetSphere(RigidBodyInstanceParam* sphere_param, sead::Heap* heap,
                          const sead::Vector3f& position,
                          const LayerMaskBuilder* layer_mask_builder = nullptr);

    RigidBody* mSphere;
};

}  // namespace ksys::phys
