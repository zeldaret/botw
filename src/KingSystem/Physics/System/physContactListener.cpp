#include "KingSystem/Physics/System/physContactListener.h"
#include <Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpCollisionEvent.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactPointEvent.h>
#include <Havok/Physics2012/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadMemUtil.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

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
    _20.allocBufferAssert(mLayerCount, nullptr);
    for (u32 i = 0; i < mLayerCount; ++i) {
        _20[i].allocBufferAssert(mLayerCount, nullptr);
    }

    _30.allocBufferAssert(mLayerCount, nullptr);
    for (u32 i = 0; i < mLayerCount; ++i) {
        auto& row = _30[i];
        row.allocBufferAssert(mLayerCount, nullptr);

        for (u32 j = 0; j < mLayerCount; ++j) {
            if (j >= i) {
                row[j] = new (heap) ContactUnk1(mLayerBase + i);
            } else {
                row[j] = _30[j][i];
            }
        }
    }
    // NOLINTEND(cppcoreguidelines-narrowing-conversions)

    _48 = sead::Mathu::roundUpPow2(mLayerCount * mLayerCount, 0x20);
    _40 = ::operator new[](_48, heap, 0x20);
    clearTable();
}

void ContactListener::clearTable() {
    sead::MemUtil::fillZero(_40, _48);
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
        regularContactPointCallback(event, body_a, body_b);
    }
}

void ContactListener::handleCollisionRemoved(const hkpCollisionEvent& event, RigidBody* body_a,
                                             RigidBody* body_b) {
    unregisterForEndOfStepContactPointCallbacks(event);

    const auto layer_a = body_a->getContactLayer();
    const auto layer_b = body_b->getContactLayer();

    if (auto* unk = body_a->getCollisionInfo())
        mMgr->x_19(unk, body_a, body_b);

    if (auto* unk = body_b->getCollisionInfo())
        mMgr->x_19(unk, body_b, body_a);

    const auto i = int(layer_a - mLayerBase);
    const auto j = int(layer_b - mLayerBase);
    ContactUnk1* unk = _30[i][j];
    if (unk->_68) {
        const auto layer_a_ = int(layer_a);
        const auto layer_unk = unk->_50;
        const bool body_a_first = layer_a_ == layer_unk;
        auto* body1 = body_a_first ? body_a : body_b;
        auto* body2 = body_a_first ? body_b : body_a;
        mMgr->x_20(unk, body1, body2);
    }
}

}  // namespace ksys::phys
