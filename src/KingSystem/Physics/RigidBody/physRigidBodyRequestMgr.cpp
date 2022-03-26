#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::phys {

static RigidBodyRequestMgr::Config sRigidBodyRequestMgrConfig;
static bool sEnableLinearVelocityChecks;

RigidBodyRequestMgr::RigidBodyRequestMgr() = default;

RigidBodyRequestMgr::~RigidBodyRequestMgr() {
    for (int i = 0; i < NumRigidBodyBuffers; ++i) {
        mRigidBodies1[i].freeBuffer();
        mOobRigidBodies[i].freeBuffer();
    }

    _38.freeBuffer();
    _50.freeBuffer();
    mImpulseEntries.freeBuffer();
    _b0.freeBuffer();
    _c8.freeBuffer();
    _e0.freeBuffer();
    _120.freeBuffer();
    _138.freeBuffer();
    mImpulseEntriesPool.freeBuffer();
    mMotionAccessors.freeBuffer();

    if (mContactPoints) {
        ksys::phys::LayerContactPointInfo::free(mContactPoints);
        mContactPoints = nullptr;
    }
}

void RigidBodyRequestMgr::init(sead::Heap* heap) {
    constexpr int Buffer138Size = 0x800;

    mImpulseEntriesPool.allocBufferAssert(0x100, heap);
    _118 = 0;

    _120.allocBufferAssert(0x100, heap);
    _130 = 0;

    for (int i = 0; i < NumRigidBodyBuffers; ++i) {
        mRigidBodies1[i].alloc(0x2000, heap);
        mOobRigidBodies[i].alloc(0x100, heap);
    }

    _38.alloc(0x800, heap);
    _50.alloc(0x800, heap);
    mImpulseEntries.alloc(0x100, heap);
    _b0.alloc(0x100, heap);
    mMotionAccessors.allocBuffer(0x400, heap);
    _138.allocBufferAssert(Buffer138Size, heap);
    _c8.alloc(0x800, heap);
    _e0.alloc(Buffer138Size, heap);

    for (int i = 0; i < Buffer138Size; ++i) {
        _e0.push(&_138[i]);
    }

    mNumEntitiesInWorld = 0;

    mContactPoints =
        LayerContactPointInfo::make(heap, 0x1000, 11, "RigidBodyRequestMgr::Water", 0, 0, 0);

    mContactPoints->setCallback(&mCallback);
    mContactPoints->set30(1);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityObject);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntitySmallObject);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityGroundObject);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityTree);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityRope);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityRagdoll);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityNPC);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityPlayer);
    mContactPoints->registerLayerPair(ContactLayer::EntityGround, ContactLayer::EntityPlayer);
    mContactPoints->registerLayerPair(ContactLayer::EntityGround, ContactLayer::EntityObject);
    mContactPoints->registerLayerPair(ContactLayer::EntityGround, ContactLayer::EntitySmallObject);

    mWaterIceSubmatIdx = MaterialMask::getSubMaterialIdx(Material::Water, "Water_Ice");
    mWaterHotSubmatIdx = MaterialMask::getSubMaterialIdx(Material::Water, "Water_Hot");
    mWaterPoisonSubmatIdx = MaterialMask::getSubMaterialIdx(Material::Water, "Water_Poison");
}

void RigidBodyRequestMgr::calc1(ContactLayerType layer_type, bool paused) {
    auto lock = sead::makeScopedLock(mCriticalSections[int(layer_type)]);
    ScopedWorldLock world_lock{layer_type};

    if (!paused && layer_type == ContactLayerType::Entity)
        processImpulseEntries();

    processOobRigidBodyEntries(layer_type);
}

void RigidBodyRequestMgr::processImpulseEntries() {
    while (auto* impulse = mImpulseEntries.pop()) {
        if (auto* tag = impulse->body_a->getUserTag())
            tag->onImpulse(impulse->body_a, impulse->body_b, impulse->impulse_a);
        else
            impulse->body_a->onImpulse(impulse->body_b, impulse->impulse_a);
    }
    _118 = 0;
}

void RigidBodyRequestMgr::processOobRigidBodyEntries(ContactLayerType layer_type) {
    while (auto* body = mOobRigidBodies[int(layer_type)].pop()) {
        if (auto* tag = body->getUserTag())
            tag->onMaxPositionExceeded(body);
        else
            body->onMaxPositionExceeded();
    }
}

bool RigidBodyRequestMgr::pushRigidBody(ContactLayerType type, RigidBody* body) {
    static_cast<void>(mRigidBodies1[int(type)].getSize());
    return mRigidBodies1[int(type)].push(body);
}

bool RigidBodyRequestMgr::registerMotionAccessor(MotionAccessor* accessor) {
    auto lock = sead::makeScopedLock(mCS);
    bool ok = !mMotionAccessors.isFull();
    mMotionAccessors.pushBack(accessor);
    return ok;
}

bool RigidBodyRequestMgr::deregisterMotionAccessor(MotionAccessor* accessor) {
    auto lock = sead::makeScopedLock(mCS);

    int idx = mMotionAccessors.indexOf(accessor);
    if (idx < 0)
        return false;

    mMotionAccessors.erase(idx);
    return true;
}

RigidBodyRequestMgr::Config& RigidBodyRequestMgr::Config::get() {
    return sRigidBodyRequestMgrConfig;
}

bool RigidBodyRequestMgr::Config::isLinearVelocityTooHigh(const sead::Vector3f& velocity) {
    if (!sEnableLinearVelocityChecks)
        return false;

    return velocity.squaredLength() > get().linear_velocity_threshold_sq;
}

void RigidBodyRequestMgr::Config::enableLinearVelocityChecks(bool enable) {
    sEnableLinearVelocityChecks = enable;
}

}  // namespace ksys::phys
