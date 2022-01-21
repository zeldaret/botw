#include "KingSystem/Physics/System/physContactListener.h"
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpCollisionEvent.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactPointEvent.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadMemUtil.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

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

}  // namespace ksys::phys
