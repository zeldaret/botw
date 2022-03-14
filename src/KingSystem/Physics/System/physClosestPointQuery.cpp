#include "KingSystem/Physics/System/physClosestPointQuery.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/physLayerMaskBuilder.h"

namespace ksys::phys {

ClosestPointQuery::ClosestPointQuery(RigidBody* body, QueryContactPointInfo* contact_point_info)
    : mBody(body), mContactPointInfo(contact_point_info) {
    reset();
}

ClosestPointQuery::~ClosestPointQuery() = default;

void ClosestPointQuery::reset() {
    mIsSuccess = false;
    _18 = 0;
}

void ClosestPointQuery::setLayerMasks(const LayerMaskBuilder& builder) {
    mContactPointInfo->setLayerMasks(builder);
}

bool ClosestPointQuery::isSuccess() const {
    return mIsSuccess;
}

void ClosestPointQuery::setLayerMasksAndBodyCollisionFilterInfo(const LayerMaskBuilder& builder) {
    EntityCollisionMask mask;
    mask.data.query_custom_receiver_layer_mask =
        builder.getMasks()[int(ContactLayerType::Entity)].layers;
    mask.data.layer = ContactLayer::EntityQueryCustomReceiver;
    mBody->setCollisionFilterInfo(mask.raw);

    setLayerMasks(builder);
}

}  // namespace ksys::phys
