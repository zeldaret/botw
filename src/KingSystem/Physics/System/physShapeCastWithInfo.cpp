#include "KingSystem/Physics/System/physShapeCastWithInfo.h"
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>
#include <Havok/Physics2012/Collide/Query/Collector/PointCollector/hkpAllCdPointCollector.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorld.h>
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

ShapeCastWithInfo::ShapeCastWithInfo(RigidBody* body, int num_contact_points, Mode mode,
                                     const sead::SafeString& name, LowPriority low_priority)
    : ShapeCast(body, nullptr, mode) {
    mStatus = Status::_1;
    auto* heap = System::instance()->getPhysicsTempHeap(low_priority);
    mContactPointInfo = QueryContactPointInfo::make(heap, num_contact_points, name, 0, 0);
}

ShapeCastWithInfo::ShapeCastWithInfo(RigidBody* body, QueryContactPointInfo* contact_point_info,
                                     Mode mode)
    : ShapeCast(body, contact_point_info, mode) {}

ShapeCastWithInfo::~ShapeCastWithInfo() {
    if (mStatus == Status::_1 || mStatus == Status::_3)
        QueryContactPointInfo::free(mContactPointInfo);
}

// NON_MATCHING: mMode test + regalloc
bool ShapeCastWithInfo::executeQuery(WeldClosestPoints weld_closest_points) {
    if (mMode == Mode::_1 || mMode == Mode::_0) {
        FilteredClosestCdPointCollector cast_collector{mBody, mContactPointInfo};
        hkpAllCdPointCollector start_collector;
        return doExecuteQuery(cast_collector, &start_collector, weld_closest_points,
                              OnlyLockIfNeeded::Yes);
    } else {
        hkpAllCdPointCollector cast_collector;
        hkpAllCdPointCollector start_collector;
        return doExecuteQuery(cast_collector, &start_collector, weld_closest_points,
                              OnlyLockIfNeeded::Yes);
    }
}

void ShapeCastWithInfo::doCast(const hkpLinearCastInput& input, hkpCdPointCollector& cast_collector,
                               hkpCdPointCollector* start_collector) {
    hkTransformf transform;
    const auto translate = mFrom;
    transform.set(toHkQuat(mRotation), toHkVec4(translate));

    hkpRigidBody* hk_body = mBody->getHkBody();
    hkpCollidable collidable{hk_body->getCollidable()->getShape(),
                             hk_body->getMotion()->getMotionState()};
    collidable.setTransform(&transform);
    collidable.setCollisionFilterInfo(hk_body->getCollisionFilterInfo());

    auto* world = System::instance()->getHavokWorld(mBody->getLayerType());
    world->linearCast(&collidable, input, cast_collector, start_collector);
}

SphereCast::SphereCast(ContactLayer layer, GroundHit ground_hit, SystemGroupHandler* group_handler,
                       int num_contact_points, ShapeCast::Mode mode, const sead::Vector3f& from,
                       float sphere_radius, const sead::SafeString& name, LowPriority low_priority)
    : ShapeCastWithInfo(nullptr, num_contact_points, mode, name, low_priority) {
    auto* heap = System::instance()->getPhysicsTempHeap(low_priority);

    SphereParam sphere_param;
    sphere_param.name = sead::SafeString::cEmptyString.cstr();
    sphere_param.radius = sphere_radius;
    sphere_param.translate = from;
    sphere_param.contact_layer = layer;
    sphere_param.groundhit = ground_hit;
    sphere_param.motion_type = MotionType::Fixed;
    sphere_param.system_group_handler = group_handler;
    sphere_param._90 = true;

    mSphere = SphereRigidBody::make(&sphere_param, heap);
    mBody = mSphere;
    mStatus = Status::_3;
}

SphereCast::~SphereCast() {
    if (mStatus == Status::_2 || mStatus == Status::_3)
        delete mSphere;
}

void SphereCast::setRadius(float radius) {
    mSphere->setRadius(radius);
    mSphere->x_40();
}

}  // namespace ksys::phys
