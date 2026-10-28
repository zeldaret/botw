#include "KingSystem/Physics/RigidBody/physRigidBodySetFromResource.h"
#include <Havok/Common/Serialize/Util/hkNativePackfileUtils.h>
#include <Havok/Common/Serialize/Util/hkRootLevelContainer.h>
#include <Havok/Physics2012/Dynamics/World/hkpPhysicsSystem.h>
#include <Havok/Physics2012/Utilities/Serialize/hkpPhysicsData.h>
#include <cstring>
#include "KingSystem/Physics/RigidBody/physRigidBodyFromResource.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyResource.h"

namespace ksys::phys {

RigidBodySetFromResource::RigidBodySetFromResource(const sead::SafeString& name,
                                                   RigidBodyResource* resource)
    : RigidBodySet(name), mResource(resource) {}

RigidBodySetFromResource::~RigidBodySetFromResource() {
    finalize();
}

// NON_MATCHING: the Havok rigid body pointer is loaded before getVolume is called instead of
// after, which changes register allocation and stack layout (equivalent)
bool RigidBodySetFromResource::init(const RigidBodySetParamAccessor& accessor, sead::Heap* heap) {
    // Copy the resource data and load it in place.
    mBufferSize = mResource->getRawSize();
    mBuffer = new (heap, 0x10) u8[mBufferSize];
    std::memcpy(mBuffer, mResource->getRawData(), mBufferSize);

    const char* error;
    auto* container = static_cast<hkRootLevelContainer*>(hkNativePackfileUtils::loadInPlace(
        mBuffer, static_cast<int>(mBufferSize), nullptr, &error));
    auto* physics_data = container->findObject<hkpPhysicsData>();
    const auto& hk_bodies = physics_data->getPhysicsSystems()[0]->getRigidBodies();

    const int num_bodies = hk_bodies.getSize();
    mRigidBodies.allocBuffer(num_bodies, heap);

    for (int i = 0; i < num_bodies; ++i) {
        RigidBodyInstanceParam param;
        accessor.makeInstanceParam(i, &param);

        const auto layer_type = getContactLayerType(param.contact_layer);
        auto* body = new (heap) RigidBodyFromResource(accessor.getVolume(i), hk_bodies[i],
                                                      layer_type, heap, RigidBody::Type::_2);
        mRigidBodies.pushBack(body);
        body->setUpdateRequestedFlag();

        if (!body->init(param, heap)) {
            body->processUpdateRequests();
            return false;
        }

        body->setCollisionFilterInfo(0);

        if (param.contact_layer == ContactLayer::SensorCustomReceiver) {
            body->setSensorCustomReceiver(param.receiver_mask, param.system_group_handler);
        } else if (param.groundhit_mask != 0) {
            body->setGroundHitMask(param.contact_layer, param.groundhit_mask);
        } else {
            body->setContactLayerAndGroundHitAndHandler(param.contact_layer, param.groundhit,
                                                        param.system_group_handler);
        }

        body->clearEntityMotionFlag20(!param.ignore_normal_for_impulse);
        body->enableGroundCollision(!param.no_hit_ground);
        body->enableWaterCollision(!param.no_hit_water);
        body->setNoCharStandingOn(param.no_char_standing_on);
        body->setContactMask(param.contact_mask);
        body->setEntityMotionFlag1(param.always_character_mass_scaling);
        body->processUpdateRequests();
    }

    return true;
}

// NON_MATCHING: regalloc (the address of mRigidBodies is kept in a register)
void RigidBodySetFromResource::finalize() {
    for (int i = 0, n = mRigidBodies.size(); i < n; ++i) {
        mRigidBodies[i]->removeFromWorldImmediately();
        delete mRigidBodies[i];
    }
    mRigidBodies.freeBuffer();

    if (mBuffer) {
        hkNativePackfileUtils::unloadInPlace(mBuffer, static_cast<int>(mBufferSize));
        delete[] mBuffer;
        mBuffer = nullptr;
    }
}

}  // namespace ksys::phys
