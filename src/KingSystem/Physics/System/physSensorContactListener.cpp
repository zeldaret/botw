#include "KingSystem/Physics/System/physSensorContactListener.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactLayerCollisionInfo.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

SensorContactListener* SensorContactListener::make(ContactMgr* mgr, sead::Heap* heap) {
    auto* listener = new (heap) SensorContactListener(mgr);
    listener->init(heap);
    return listener;
}

SensorContactListener::SensorContactListener(ContactMgr* mgr)
    : ContactListener(mgr, ContactLayerType::Sensor, LastSensor - FirstSensor + 1) {}

SensorContactListener::~SensorContactListener() = default;

void SensorContactListener::handleCollisionAdded(const hkpCollisionEvent& event, RigidBody* body_a,
                                                 RigidBody* body_b) {
    registerForEndOfStepContactPointCallbacks(event);

    const auto layer_a = body_a->getContactLayer();
    const auto layer_b = body_b->getContactLayer();

    const auto rlayer_a = int(layer_a - mLayerBase);
    const auto rlayer_b = int(layer_b - mLayerBase);

    if (body_a->getContactMask().isOnBit(rlayer_b) || body_b->getContactMask().isOnBit(rlayer_a))
        return;

    if (body_a->getCollisionInfo() && body_a->getCollisionInfo()->isLayerEnabled(layer_b))
        mMgr->registerCollision(body_a->getCollisionInfo(), body_a, body_b);

    if (body_b->getCollisionInfo() && body_b->getCollisionInfo()->isLayerEnabled(layer_a))
        mMgr->registerCollision(body_b->getCollisionInfo(), body_b, body_a);

    if (areContactsTrackedForLayerPair(rlayer_a, rlayer_b)) {
        auto* layer_col_info = getContactLayerCollisionInfo(rlayer_a, rlayer_b);
        if (body_a->isAddedToWorld() && body_b->isAddedToWorld()) {
            const auto layer_a_ = int(layer_a);
            const auto tracked_layer = layer_col_info->getLayer();
            const bool body_a_first = layer_a_ == tracked_layer;
            auto* body1 = body_a_first ? body_a : body_b;
            auto* body2 = body_a_first ? body_b : body_a;
            mMgr->registerCollision(layer_col_info, body1, body2);
        }
    }
}

bool SensorContactListener::manifoldContactPointCallback(const hkpContactPointEvent& event,
                                                         RigidBody* body_a, RigidBody* body_b) {
    [[maybe_unused]] auto* filter = System::instance()->getGroupFilter(mLayerType);
    const auto layer_a = body_a->getContactLayer();
    const auto layer_b = body_b->getContactLayer();

    return contactPointCallbackImpl(0, 0, body_a, body_b, layer_a, layer_b, event);
}

bool SensorContactListener::regularContactPointCallback(
    const hkpContactPointEvent& event, RigidBody* body_a, RigidBody* body_b,
    sead::SafeArray<u32, 2>* out_material_masks) {
    [[maybe_unused]] auto* filter = System::instance()->getGroupFilter(mLayerType);

    RigidBody::CollisionMasks masks_a, masks_b;
    sead::Vector3f contact_point_pos;

    storeToVec3(&contact_point_pos, event.m_contactPoint->getPosition());
    body_a->getCollisionMasks(&masks_a, event.getShapeKeys(0), contact_point_pos);
    body_b->getCollisionMasks(&masks_b, event.getShapeKeys(1), contact_point_pos);

    const auto layer_a = body_a->getContactLayer();
    const auto layer_b = body_b->getContactLayer();

    const auto rlayer_a = layer_a - int(mLayerBase);
    const auto rlayer_b = layer_b - int(mLayerBase);
    const auto& entries = mTrackedContactPointLayers[rlayer_a][rlayer_b];

    const bool result = contactPointCallbackImpl(0, 0, body_a, body_b, layer_a, layer_b, event);

    if (body_a->getIgnoredLayers().isOnBit(rlayer_b) &&
        body_b->getIgnoredLayers().isOnBit(rlayer_a)) {
        const auto notify_result =
            notifyContactPointInfo(body_a, body_b, layer_a, layer_b, masks_a, masks_b, event, true);

        for (int idx = 0; idx < entries.size(); ++idx) {
            notifyLayerContactPointInfo(*entries[idx], notify_result, body_a, body_b, layer_a,
                                        layer_b, masks_a.material_mask, masks_b.material_mask,
                                        event);
        }
    }

    return result;
}

}  // namespace ksys::phys
