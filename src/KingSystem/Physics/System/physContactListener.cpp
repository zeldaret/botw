#include "KingSystem/Physics/System/physContactListener.h"
#include <Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpCollisionEvent.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactPointEvent.h>
#include <Havok/Physics2012/Dynamics/Collide/hkpSimpleConstraintContactMgr.h>
#include <Havok/Physics2012/Dynamics/Constraint/Contact/hkpContactPointProperties.h>
#include <Havok/Physics2012/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadMemUtil.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactLayerCollisionInfo.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physLayerContactPointInfo.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

ContactListener::ContactListener(ContactMgr* mgr, ContactLayerType layer_type, int layer_count)
    : mMgr(mgr), mLayerType(layer_type), mLayerBase(getContactLayerBase(layer_type)),
      mLayerCount(layer_count) {}

ContactListener::~ContactListener() = default;

void ContactListener::init(sead::Heap* heap) {
    // NOLINTBEGIN(cppcoreguidelines-narrowing-conversions)
    mTrackedContactPointLayers.allocBufferAssert(mLayerCount, nullptr);
    for (u32 i = 0; i < mLayerCount; ++i) {
        mTrackedContactPointLayers[i].allocBufferAssert(mLayerCount, nullptr);
    }

    mCollisionInfoPerLayerPair.allocBufferAssert(mLayerCount, nullptr);
    for (u32 i = 0; i < mLayerCount; ++i) {
        auto& row = mCollisionInfoPerLayerPair[i];
        row.allocBufferAssert(mLayerCount, nullptr);

        for (u32 j = 0; j < mLayerCount; ++j) {
            if (j >= i) {
                row[j] = new (heap) ContactLayerCollisionInfo(mLayerBase + i);
            } else {
                row[j] = mCollisionInfoPerLayerPair[j][i];
            }
        }
    }
    // NOLINTEND(cppcoreguidelines-narrowing-conversions)

    mTrackedLayersBufferSize = sead::Mathu::roundUpPow2(mLayerCount * mLayerCount, 0x20);
    mTrackedLayers = new (heap, 0x20) u8[mTrackedLayersBufferSize];
    clearTable();
}

void ContactListener::clearTable() {
    sead::MemUtil::fillZero(mTrackedLayers, mTrackedLayersBufferSize);
}

void ContactListener::collisionAddedCallback(const hkpCollisionEvent& event) {
    auto* bodyA = getRigidBody(*event.getBody(0));
    auto* bodyB = getRigidBody(*event.getBody(1));
    handleCollisionAdded(event, bodyA, bodyB);
    bodyA->onCollisionAdded();
    bodyB->onCollisionAdded();
}

void ContactListener::collisionRemovedCallback(const hkpCollisionEvent& event) {
    auto* bodyA = getRigidBody(*event.getBody(0));
    auto* bodyB = getRigidBody(*event.getBody(1));
    handleCollisionRemoved(event, bodyA, bodyB);
    bodyA->onCollisionRemoved();
    bodyB->onCollisionRemoved();
}

void ContactListener::contactPointCallback(const hkpContactPointEvent& event) {
    RigidBody* body_a = getRigidBody(*event.getBody(0));
    RigidBody* body_b = getRigidBody(*event.getBody(1));

    if (event.m_contactPoint->getPosition().getInt24W() == hkpCharacterRigidBody::m_magicNumber) {
        const auto layer_a = body_a->getContactLayer();
        const auto layer_b = body_b->getContactLayer();
        const u32 ignored_layers_a = ~body_a->getContactMask();
        const u32 ignored_layers_b = ~body_b->getContactMask();

        static_cast<void>(System::instance()->getGroupFilter(mLayerType));

        contactPointCallbackImpl(ignored_layers_a, ignored_layers_b, body_a, body_b, layer_a,
                                 layer_b, event);

    } else if (event.m_type == hkpContactPointEvent::TYPE_MANIFOLD) {
        manifoldContactPointCallback(event, body_a, body_b);
    } else {
        regularContactPointCallback(event, body_a, body_b, nullptr);
    }
}

bool ContactListener::manifoldContactPointCallback(const hkpContactPointEvent& event,
                                                   RigidBody* body_a, RigidBody* body_b) {
    auto* filter = System::instance()->getGroupFilter(mLayerType);

    RigidBody::CollisionMasks masks_a, masks_b;
    sead::Vector3f contact_point_pos, position, normal;
    ContactPointInfo::Event my_event;

    storeToVec3(&contact_point_pos, event.m_contactPoint->getPosition());

    body_a->getCollisionMasks(&masks_a, event.getShapeKeys(0), contact_point_pos);
    body_b->getCollisionMasks(&masks_b, event.getShapeKeys(1), contact_point_pos);

    const auto layer_a = filter->getCollisionFilterInfoLayer(masks_a.collision_filter_info);
    const auto layer_b = filter->getCollisionFilterInfoLayer(masks_b.collision_filter_info);

    if (!contactPointCallbackImpl(masks_a.ignored_layers, masks_b.ignored_layers, body_a, body_b,
                                  layer_a, layer_b, event)) {
        return false;
    }

    // Fire ContactPointInfo callbacks.

    if (auto* info = body_a->getContactPointInfo(); info && info->getContactCallback()) {
        storeToVec3(&position, event.m_contactPoint->getPosition());
        storeToVec3(&normal, event.m_contactPoint->getSeparatingNormal());
        normal *= -1;
        my_event.body = body_b;
        my_event.position = &position;
        my_event.separating_normal = &normal;
        my_event.collision_masks = &masks_b;

        auto disable = ContactPointInfo::ShouldDisableContact::No;

        info->getContactCallback()->invoke(&disable, my_event);

        if (disable == ContactPointInfo::ShouldDisableContact::Yes) {
            disableContact(event);
            return false;
        }
    }

    if (auto* info = body_b->getContactPointInfo(); info && info->getContactCallback()) {
        storeToVec3(&position, event.m_contactPoint->getPosition());
        storeToVec3(&normal, event.m_contactPoint->getSeparatingNormal());
        my_event.body = body_a;
        my_event.position = &position;
        my_event.separating_normal = &normal;
        my_event.collision_masks = &masks_a;

        auto disable = ContactPointInfo::ShouldDisableContact::No;

        info->getContactCallback()->invoke(&disable, my_event);

        if (disable == ContactPointInfo::ShouldDisableContact::Yes) {
            disableContact(event);
            return false;
        }
    }

    return true;
}

bool ContactListener::regularContactPointCallback(const hkpContactPointEvent& event,
                                                  RigidBody* body_a, RigidBody* body_b,
                                                  sead::SafeArray<u32, 2>* out_material_masks) {
    auto* filter = System::instance()->getGroupFilter(mLayerType);

    RigidBody::CollisionMasks masks_a, masks_b;
    sead::Vector3f contact_point_pos;

    storeToVec3(&contact_point_pos, event.m_contactPoint->getPosition());
    body_a->getCollisionMasks(&masks_a, event.getShapeKeys(0), contact_point_pos);
    body_b->getCollisionMasks(&masks_b, event.getShapeKeys(1), contact_point_pos);

    if (out_material_masks) {
        (*out_material_masks)[0] = masks_a.material_mask;
        (*out_material_masks)[1] = masks_b.material_mask;
    }

    const auto layer_a = filter->getCollisionFilterInfoLayer(masks_a.collision_filter_info);
    const auto layer_b = filter->getCollisionFilterInfoLayer(masks_b.collision_filter_info);
    const auto i = layer_a - int(mLayerBase);
    const auto j = layer_b - int(mLayerBase);

    const bool result = contactPointCallbackImpl(masks_a.ignored_layers, masks_b.ignored_layers,
                                                 body_a, body_b, layer_a, layer_b, event);
    if (result)
        m11(event, masks_a, masks_b, body_a, body_b);

    const auto& entries = mTrackedContactPointLayers[i][j];

    if (layer_a == ContactLayer::EntityRagdoll || layer_b == ContactLayer::EntityRagdoll)
        clearCallbackDelay(event);

    // Fire rigid body callbacks.
    bool callbacks_ok = true;
    if (auto* callback = body_a->getContactCallback()) {
        RigidBodyContactEvent my_event{body_b, &masks_b, event.getShapeKeys(1), &event};
        callbacks_ok &= callback->invoke(my_event);
    }
    if (auto* callback = body_b->getContactCallback()) {
        RigidBodyContactEvent my_event{body_a, &masks_a, event.getShapeKeys(0), &event};
        callbacks_ok &= callback->invoke(my_event);
    }

    auto notify_result = notifyContactPointInfo(body_a, body_b, layer_a, layer_b, masks_a, masks_b,
                                                event, callbacks_ok);

    for (int idx = 0; idx < entries.size(); ++idx) {
        notifyLayerContactPointInfo(*entries[idx], notify_result, body_a, body_b, layer_a, layer_b,
                                    masks_a.material_mask, masks_b.material_mask, event);
    }

    return result;
}

int ContactListener::notifyContactPointInfo(RigidBody* body_a, RigidBody* body_b,
                                            ContactLayer layer_a, ContactLayer layer_b,
                                            const RigidBodyCollisionMasks& masks_a,
                                            const RigidBodyCollisionMasks& masks_b,
                                            const hkpContactPointEvent& event, bool callbacks_ok) {
    const hkReal distance = event.m_contactPoint->getDistance();
    const bool should_notify = callbacks_ok && !mDisableContactPointInfoNotifications;
    auto* info_a = body_a->getContactPointInfo();
    auto* info_b = body_b->getContactPointInfo();
    const bool contact_disabled = isContactDisabled(event);

    ContactPoint point;
    point.separating_distance = distance;

    int result = 1;

    if (info_b && info_b->isLayerSubscribed(layer_a) &&
        info_b->testContactPointDistance(distance) && (info_b->get34() == 0 || !contact_disabled)) {
        if (should_notify) {
            point.body_a = body_b;
            point.body_b = body_a;
            point.material_mask_a = MaterialMaskData(masks_b.material_mask);
            point.material_mask_b = MaterialMaskData(masks_a.material_mask);
            point.shape_key_a = getShapeKeyOrMinus1(event.getShapeKeys(1));
            point.shape_key_b = getShapeKeyOrMinus1(event.getShapeKeys(0));
            storeToVec3(&point.position, event.m_contactPoint->getPosition());
            storeToVec3(&point.separating_normal, event.m_contactPoint->getSeparatingNormal());

            if (mMgr->registerContactPoint(body_b->getContactPointInfo(), point, masks_a,
                                           distance < 0)) {
                disableContact(event);
            }

            result = 2;
        }

        if (info_b->isLayerInMask2(layer_a))
            clearCallbackDelay(event);
    }

    if (info_a && info_a->isLayerSubscribed(layer_b) &&
        info_a->testContactPointDistance(distance) && (info_a->get34() == 0 || !contact_disabled)) {
        if (should_notify) {
            point.body_a = body_a;
            point.body_b = body_b;
            if (result == 1) {
                storeToVec3(&point.position, event.m_contactPoint->getPosition());
                storeToVec3(&point.separating_normal, event.m_contactPoint->getSeparatingNormal());
            }
            point.material_mask_a = MaterialMaskData(masks_a.material_mask);
            point.material_mask_b = MaterialMaskData(masks_b.material_mask);
            point.shape_key_a = getShapeKeyOrMinus1(event.getShapeKeys(0));
            point.shape_key_b = getShapeKeyOrMinus1(event.getShapeKeys(1));
            point.separating_normal *= -1;

            if (mMgr->registerContactPoint(body_a->getContactPointInfo(), point, masks_b,
                                           !(distance < 0))) {
                disableContact(event);
            }

            result = 2;
        }

        if (info_a->isLayerInMask2(layer_b))
            clearCallbackDelay(event);
    }

    return result;
}

// NON_MATCHING: branching (shape_key_b store), layer_a not being saved on the stack
void ContactListener::notifyLayerContactPointInfo(const TrackedContactPointLayer& tracked_layer,
                                                  int, RigidBody* body_a, RigidBody* body_b,
                                                  ContactLayer layer_a, ContactLayer layer_b,
                                                  u32 material_a, u32 material_b,
                                                  const hkpContactPointEvent& event) {
    if (tracked_layer.do_not_delay_callback)
        clearCallbackDelay(event);

    if (mDisableContactPointInfoNotifications)
        return;

    const hkReal distance = event.m_contactPoint->getDistance();
    if (!tracked_layer.info->testContactPointDistance(distance))
        return;

    if (tracked_layer.info->get34() != 0 && isContactDisabled(event))
        return;

    ContactPoint point;
    storeToVec3(&point.position, event.m_contactPoint->getPosition());
    storeToVec3(&point.separating_normal, event.m_contactPoint->getSeparatingNormal());

    if (auto* callback = tracked_layer.info->getCallback()) {
        if (tracked_layer.layer == layer_a) {
            LayerContactPointInfo::ContactEvent my_event;
            my_event.body_a = body_a;
            my_event.body_b = body_b;
            my_event.point_position = &point.position;
            my_event.layer_a = layer_a;
            my_event.layer_b = layer_b;
            my_event.material_a = MaterialMaskData(material_a);
            my_event.material_b = MaterialMaskData(material_b);
            if (!callback->invoke(my_event))
                return;
        } else {
            LayerContactPointInfo::ContactEvent my_event;
            my_event.body_a = body_b;
            my_event.body_b = body_a;
            my_event.point_position = &point.position;
            my_event.layer_a = layer_b;
            my_event.layer_b = layer_a;
            my_event.material_a = MaterialMaskData(material_b);
            my_event.material_b = MaterialMaskData(material_a);
            if (!callback->invoke(my_event))
                return;
        }
    }

    if (tracked_layer.layer == layer_a) {
        point.body_a = body_a;
        point.body_b = body_b;
        point.material_mask_a = MaterialMaskData(material_a);
        point.material_mask_b = MaterialMaskData(material_b);
        point.shape_key_a = getShapeKeyOrMinus1(event.getShapeKeys(0));
        point.shape_key_b = getShapeKeyOrMinus1(event.getShapeKeys(1));
        point.separating_normal *= -1;
        point.separating_distance = distance < 0 ? distance : 0;
        mMgr->registerContactPoint(tracked_layer.info, point, !(distance < 0));
    } else {
        point.body_a = body_b;
        point.body_b = body_a;
        point.material_mask_a = MaterialMaskData(material_b);
        point.material_mask_b = MaterialMaskData(material_a);
        point.shape_key_a = getShapeKeyOrMinus1(event.getShapeKeys(1));
        point.shape_key_b = getShapeKeyOrMinus1(event.getShapeKeys(0));
        point.separating_distance = distance < 0 ? distance : 0;
        mMgr->registerContactPoint(tracked_layer.info, point, distance < 0);
    }
}

void ContactListener::handleCollisionAdded(const hkpCollisionEvent& event, RigidBody* body_a,
                                           RigidBody* body_b) {
    registerForEndOfStepContactPointCallbacks(event);

    const auto layer_a = body_a->getContactLayer();
    const auto layer_b = body_b->getContactLayer();

    if (body_a->getCollisionInfo() && body_a->getCollisionInfo()->isLayerEnabled(layer_b))
        mMgr->registerCollision(body_a->getCollisionInfo(), body_a, body_b);

    if (body_b->getCollisionInfo() && body_b->getCollisionInfo()->isLayerEnabled(layer_a))
        mMgr->registerCollision(body_b->getCollisionInfo(), body_b, body_a);

    const auto i = int(layer_a - mLayerBase);
    const auto j = int(layer_b - mLayerBase);
    if (areContactsTrackedForLayerPair(i, j)) {
        auto* layer_col_info = getContactLayerCollisionInfo(i, j);
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

void ContactListener::handleCollisionRemoved(const hkpCollisionEvent& event, RigidBody* body_a,
                                             RigidBody* body_b) {
    unregisterForEndOfStepContactPointCallbacks(event);

    const auto layer_a = body_a->getContactLayer();
    const auto layer_b = body_b->getContactLayer();

    if (auto* info = body_a->getCollisionInfo())
        mMgr->unregisterCollision(info, body_a, body_b);

    if (auto* info = body_b->getCollisionInfo())
        mMgr->unregisterCollision(info, body_b, body_a);

    const auto i = int(layer_a - mLayerBase);
    const auto j = int(layer_b - mLayerBase);
    auto* info = getContactLayerCollisionInfo(i, j);
    if (!info->getCollidingBodies().isEmpty()) {
        const auto layer_a_ = int(layer_a);
        const auto tracked_layer = info->getLayer();
        const bool body_a_first = layer_a_ == tracked_layer;
        auto* body1 = body_a_first ? body_a : body_b;
        auto* body2 = body_a_first ? body_b : body_a;
        mMgr->unregisterCollision(info, body1, body2);
    }
}

bool ContactListener::areContactsTrackedForLayerPair(u32 rlayer_a, u32 rlayer_b) const {
    return mTrackedLayers[mLayerCount * rlayer_a + rlayer_b];
}

ContactLayerCollisionInfo* ContactListener::getContactLayerCollisionInfo(u32 rlayer_a,
                                                                         u32 rlayer_b) {
    return mCollisionInfoPerLayerPair[int(rlayer_a)][int(rlayer_b)];
}

ContactLayerCollisionInfo* ContactListener::trackLayerPair(ContactLayer layer_a,
                                                           ContactLayer layer_b) {
    const auto [i, j] = convertToRelativeLayer(layer_a, layer_b);
    (&mTrackedLayers[mLayerCount * i])[j] = true;
    (&mTrackedLayers[mLayerCount * j])[i] = true;
    return mCollisionInfoPerLayerPair[i][j];
}

void ContactListener::addLayerPairForContactPointInfo(LayerContactPointInfo* info,
                                                      ContactLayer layer1, ContactLayer layer2,
                                                      bool enabled) {
    auto lock = sead::makeScopedLock(mCS);
    const auto [i, j] = convertToRelativeLayer(layer1, layer2);

    const auto set = [&](TrackedContactPointLayer* entry) {
        if (!entry)
            return;
        entry->info = info;
        entry->layer = layer1;
        entry->do_not_delay_callback = enabled;
    };

    auto& row_i = mTrackedContactPointLayers[i];
    auto& row_j = mTrackedContactPointLayers[j];
    set(row_i[j].emplaceBack());
    set(row_j[i].emplaceBack());
}

void ContactListener::removeLayerPairsForContactPointInfo(LayerContactPointInfo* info) {
    auto lock = sead::makeScopedLock(mCS);
    for (int i = 0; i < info->getLayerEntries().size(); ++i) {
        auto* entry = info->getLayerEntries()[i];
        removeLayerPairForContactPointInfo(info, entry->layer1, entry->layer2);
    }
}

// NON_MATCHING: enum-to-int conversion (stp should be 2 str), reordering, branching
void ContactListener::removeLayerPairForContactPointInfo(LayerContactPointInfo* info,
                                                         ContactLayer layer1, ContactLayer layer2) {
    const auto [i, j] = convertToRelativeLayer(layer1, layer2);
    auto& row_i = mTrackedContactPointLayers[i];
    auto& row_j = mTrackedContactPointLayers[j];
    auto& ij = row_i[j];
    auto& ji = row_j[i];

    for (int idx = 0; idx < ij.size(); ++idx) {
        if (ij[idx]->info == info) {
            ij.erase(idx);
            break;
        }
    }

    for (int idx = 0; idx < ji.size(); ++idx) {
        if (ji[idx]->info == info) {
            ji.erase(idx);
            break;
        }
    }
}

void ContactListener::unregisterCollisionWithBody(RigidBody* body) {
    const u32 rlayer = body->getContactLayer() - mLayerBase;
    auto& column = mCollisionInfoPerLayerPair[int(rlayer)];
    for (u32 i = 0; i < mLayerCount; ++i) {
        ContactLayerCollisionInfo* info = column[int(i)];
        mMgr->unregisterCollisionWithBody(info, body);
    }
}

bool ContactListener::contactPointCallbackImpl(u32 ignored_layers_a, u32 ignored_layers_b,
                                               RigidBody* body_a, RigidBody* body_b,
                                               ContactLayer layer_a, ContactLayer layer_b,
                                               const hkpContactPointEvent& event) {
    disableContact(event);
    return false;
}

}  // namespace ksys::phys
