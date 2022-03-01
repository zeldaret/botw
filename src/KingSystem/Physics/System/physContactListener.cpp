#include "KingSystem/Physics/System/physContactListener.h"
#include <Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Havok/Physics2012/Collide/Agent/ContactMgr/hkpContactMgr.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpCollisionEvent.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactPointEvent.h>
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

static RigidBody* getRigidBody(hkpRigidBody* hk_body) {
    // This needs to be kept in sync with the RigidBody constructor!
    return reinterpret_cast<RigidBody*>(hk_body->getUserData());
}

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
    auto* bodyA = getRigidBody(event.getBody(0));
    auto* bodyB = getRigidBody(event.getBody(1));
    handleCollisionAdded(event, bodyA, bodyB);
    bodyA->onCollisionAdded();
    bodyB->onCollisionAdded();
}

void ContactListener::collisionRemovedCallback(const hkpCollisionEvent& event) {
    auto* bodyA = getRigidBody(event.getBody(0));
    auto* bodyB = getRigidBody(event.getBody(1));
    handleCollisionRemoved(event, bodyA, bodyB);
    bodyA->onCollisionRemoved();
    bodyB->onCollisionRemoved();
}

void ContactListener::contactPointCallback(const hkpContactPointEvent& event) {
    RigidBody* body_a = getRigidBody(event.getBody(0));
    RigidBody* body_b = getRigidBody(event.getBody(1));

    if (event.m_contactPoint->getPosition().getInt24W() == hkpCharacterRigidBody::m_magicNumber) {
        const auto layer_a = body_a->getContactLayer();
        const auto layer_b = body_b->getContactLayer();
        const u32 ignored_layers_a = ~body_a->getContactMask();
        const u32 ignored_layers_b = ~body_b->getContactMask();

        static_cast<void>(System::instance()->getGroupFilter(mLayerType));

        characterControlContactPointCallback(ignored_layers_a, ignored_layers_b, body_a, body_b,
                                             layer_a, layer_b, event);

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

    if (!characterControlContactPointCallback(masks_a.ignored_layers, masks_b.ignored_layers,
                                              body_a, body_b, layer_a, layer_b, event)) {
        return false;
    }

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
            event.m_contactPointProperties->m_flags |=
                hkpContactPointProperties::CONTACT_IS_DISABLED;
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
            event.m_contactPointProperties->m_flags |=
                hkpContactPointProperties::CONTACT_IS_DISABLED;
            return false;
        }
    }

    return true;
}

void ContactListener::handleCollisionAdded(const hkpCollisionEvent& event, RigidBody* body_a,
                                           RigidBody* body_b) {
    registerForEndOfStepContactPointCallbacks(event);

    const auto layer_a = body_a->getContactLayer();
    const auto layer_b = body_b->getContactLayer();

    if (body_a->getCollisionInfo() && body_a->getCollisionInfo()->isLayerEnabled(layer_b))
        mMgr->x_17(body_a->getCollisionInfo(), body_a, body_b);

    if (body_b->getCollisionInfo() && body_b->getCollisionInfo()->isLayerEnabled(layer_a))
        mMgr->x_17(body_b->getCollisionInfo(), body_b, body_a);

    const auto i = int(layer_a - mLayerBase);
    const auto j = int(layer_b - mLayerBase);
    if (areContactsTrackedForLayerPair(i, j)) {
        auto* info = getContactLayerCollisionInfo(i, j);
        if (body_a->isFlag8Set() && body_b->isFlag8Set()) {
            const auto layer_a_ = int(layer_a);
            const auto tracked_layer = info->getLayer();
            const bool body_a_first = layer_a_ == tracked_layer;
            auto* body1 = body_a_first ? body_a : body_b;
            auto* body2 = body_a_first ? body_b : body_a;
            mMgr->x_18(info, body1, body2);
        }
    }
}

void ContactListener::handleCollisionRemoved(const hkpCollisionEvent& event, RigidBody* body_a,
                                             RigidBody* body_b) {
    unregisterForEndOfStepContactPointCallbacks(event);

    const auto layer_a = body_a->getContactLayer();
    const auto layer_b = body_b->getContactLayer();

    if (auto* info = body_a->getCollisionInfo())
        mMgr->x_19(info, body_a, body_b);

    if (auto* info = body_b->getCollisionInfo())
        mMgr->x_19(info, body_b, body_a);

    const auto i = int(layer_a - mLayerBase);
    const auto j = int(layer_b - mLayerBase);
    auto* info = getContactLayerCollisionInfo(i, j);
    if (!info->getList().isEmpty()) {
        const auto layer_a_ = int(layer_a);
        const auto tracked_layer = info->getLayer();
        const bool body_a_first = layer_a_ == tracked_layer;
        auto* body1 = body_a_first ? body_a : body_b;
        auto* body2 = body_a_first ? body_b : body_a;
        mMgr->x_20(info, body1, body2);
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
        entry->enabled = enabled;
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

void ContactListener::registerRigidBody(RigidBody* body) {
    const u32 rlayer = body->getContactLayer() - mLayerBase;
    auto& column = mCollisionInfoPerLayerPair[int(rlayer)];
    for (u32 i = 0; i < mLayerCount; ++i) {
        ContactLayerCollisionInfo* info = column[int(i)];
        mMgr->x_21(info, body);
    }
}

bool ContactListener::characterControlContactPointCallback(u32 ignored_layers_a,
                                                           u32 ignored_layers_b, RigidBody* body_a,
                                                           RigidBody* body_b, ContactLayer layer_a,
                                                           ContactLayer layer_b,
                                                           const hkpContactPointEvent& event) {
    event.m_contactPointProperties->m_flags |= hkpContactPointProperties::CONTACT_IS_DISABLED;
    return false;
}

}  // namespace ksys::phys
