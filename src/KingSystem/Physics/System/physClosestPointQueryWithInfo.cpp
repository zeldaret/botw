#include "KingSystem/Physics/System/physClosestPointQueryWithInfo.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"
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

SphereBasedClosestPointQuery::SphereBasedClosestPointQuery(
    const sead::Vector3f& position, float sphere_radius, ContactLayer layer, GroundHit ground_hit,
    SystemGroupHandler* group_handler, int num_points, const sead::SafeString& name, int a,
    LowPriority low_priority)
    : ClosestPointQueryWithInfo(nullptr, num_points, name, a, low_priority) {
    auto* heap = System::instance()->getPhysicsTempHeap(low_priority);

    SphereParam sphere_param;
    sphere_param.name = sead::SafeString::cEmptyString.cstr();
    sphere_param.radius = sphere_radius;
    sphere_param.contact_layer = layer;
    sphere_param.groundhit = ground_hit;
    sphere_param.motion_type = MotionType::Fixed;
    sphere_param._90 = true;
    sphere_param.system_group_handler = group_handler;
    makeAndSetSphere(&sphere_param, heap, position);
}

SphereBasedClosestPointQuery::SphereBasedClosestPointQuery(
    const sead::Vector3f& position, float sphere_radius, ContactLayer layer,
    const LayerMaskBuilder& layer_mask_builder, int num_points, const sead::SafeString& name, int a,
    LowPriority low_priority)
    : ClosestPointQueryWithInfo(nullptr, num_points, name, a, low_priority) {
    auto* heap = System::instance()->getPhysicsTempHeap(low_priority);

    SphereParam sphere_param;
    sphere_param.name = sead::SafeString::cEmptyString.cstr();
    sphere_param.radius = sphere_radius;
    sphere_param.contact_layer = layer;
    sphere_param.motion_type = MotionType::Fixed;
    sphere_param._90 = true;
    makeAndSetSphere(&sphere_param, heap, position, &layer_mask_builder);
}

SphereBasedClosestPointQuery::SphereBasedClosestPointQuery(
    const sead::Vector3f& position, float sphere_radius, const SensorCollisionMask& mask,
    SystemGroupHandler* group_handler, int num_points, const sead::SafeString& name, int a,
    LowPriority low_priority)
    : ClosestPointQueryWithInfo(nullptr, num_points, name, a, low_priority) {
    auto* heap = System::instance()->getPhysicsTempHeap(low_priority);

    SphereParam sphere_param;
    sphere_param.name = sead::SafeString::cEmptyString.cstr();
    sphere_param.radius = sphere_radius;
    sphere_param.contact_layer = ContactLayer::SensorCustomReceiver;
    sphere_param.groundhit = GroundHit::HitAll;
    sphere_param.receiver_mask = mask;
    sphere_param.motion_type = MotionType::Fixed;
    sphere_param.system_group_handler = group_handler;
    sphere_param._90 = true;
    makeAndSetSphere(&sphere_param, heap, position);
}

SphereBasedClosestPointQuery::SphereBasedClosestPointQuery(RigidBody* sphere,
                                                           const sead::Vector3f& position,
                                                           int num_points,
                                                           const sead::SafeString& name, int a,
                                                           LowPriority low_priority)
    : ClosestPointQueryWithInfo(sphere, num_points, name, a, low_priority) {
    [[maybe_unused]] auto* heap = System::instance()->getPhysicsTempHeap(low_priority);
    mSphere = sphere;
    mMtx.setTranslation(position);
}

SphereBasedClosestPointQuery::~SphereBasedClosestPointQuery() {
    if (mStatus == Status::_2 || mStatus == Status::_3) {
        delete mSphere;
    }
}

void SphereBasedClosestPointQuery::makeAndSetSphere(RigidBodyInstanceParam* sphere_param,
                                                    sead::Heap* heap,
                                                    const sead::Vector3f& position,
                                                    const LayerMaskBuilder* layer_mask_builder) {
    mSphere = SphereRigidBody::make(sphere_param, heap);
    mBody = mSphere;

    if (layer_mask_builder != nullptr) {
        setLayerMasksAndBodyCollisionFilterInfo(*layer_mask_builder);
    }

    if (mBody) {
        mMtx.setTranslation(position);
        mStatus = Status::_3;
    }
}

}  // namespace ksys::phys
