#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/Ragdoll/physRagdollController.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Resource/Actor/resResourceRagdollBlendWeight.h"

namespace ksys::phys {

void InstanceSet::setFlag2() {
    mFlags.set(Flag::_2);
    if (mClothSet != nullptr) {
        mFlags.set(Flag::_2);
        mFlags.set(Flag::DisableDraw);
    }
}

void InstanceSet::clothVisibleStuff() {
    if (mClothSet != nullptr) {
        mFlags.set(Flag::DisableDraw);
    }
}

void InstanceSet::setInDemo() {
    mFlags.set(Flag::InDemo);
}

void InstanceSet::resetInDemo() {
    mFlags.reset(Flag::InDemo);
}

void InstanceSet::clothVisibleStuff_0(s32 setting) {
    if (mFlags.isOn(Flag::InDemo))
        return;

    switch (setting) {
    case -2:
        mFlags.reset(Flag::Cloth2);
        mFlags.set(Flag::Cloth1);
        break;
    case -1:
        mFlags.reset(Flag::Cloth3);
        mFlags.reset(Flag::Cloth2);
        mFlags.reset(Flag::Cloth1);
        mFlags.set(Flag::Cloth2);
        mFlags.set(Flag::Cloth3);
        break;
    case 0:
        mFlags.reset(Flag::Cloth1);
        mFlags.reset(Flag::Cloth2);
        mFlags.set(Flag::Cloth3);
        break;
    case 1:
        mFlags.reset(Flag::Cloth1);
        mFlags.reset(Flag::Cloth2);
        mFlags.reset(Flag::Cloth3);
        break;
    }
}

void InstanceSet::sub_7100FB9BAC(InstanceSet* other) {
    if (other == nullptr)
        return;

    u32 idx = other->sub_7100FB9C2C();
    clothVisibleStuff_0(idx);
}

u32 InstanceSet::sub_7100FB9C2C() const {
    u32 idx;
    if (mFlags.isOn(Flag::Cloth1)) {
        idx = -2;
    } else if (mFlags.isOn(Flag::Cloth2)) {
        idx = -1;
    } else if (mFlags.isOn(Flag::Cloth3)) {
        idx = 0;
    } else {
        idx = 1;
    }
    return idx;
}

void InstanceSet::sub_7100FBA9BC() {
    for (auto& rb : mRigidBodySets) {
        rb.addToWorld();
    }

    for (auto& body : mList) {
        body->addToWorld();
    }

    if (mCharacterController != nullptr)
        mCharacterController->sub_7100F5EC30();
}

void InstanceSet::sub_7100FBACE0(phys::ContactLayer layer) {
    bool sensor = phys::getContactLayerType(layer) != ContactLayerType::Entity;

    for (auto& rb : mRigidBodySets) {
        rb.disableContactLayer(layer);
    }
    if (sensor)
        return;

    if (mRagdollController != nullptr)
        mRagdollController->sub_7101221728(layer);

    if (mCharacterController != nullptr)
        mCharacterController->enableCollisionMaybe_0(layer);
}

void InstanceSet::sub_7100FBAD74() {
    for (auto& rb : mRigidBodySets) {
        rb.disableAllContactLayers();
    }
    if (mRagdollController != nullptr) {
        mRagdollController->sub_71012217A8();
    }
    if (mCharacterController != nullptr) {
        mCharacterController->sub_7100F60604();
    }
}

void* InstanceSet::sub_7100FBAEDC(s32 idx1, s32 idx2) const {
    if (mRigidBodySets.size() <= idx1)
        return nullptr;
    return mRigidBodySets[idx1]->getRigidBody(idx2);
}

void InstanceSet::sub_7100FBB00C(phys::RigidBody* body, phys::RigidBodyParam* param) {
    if (body == nullptr)
        return;

    phys::RigidBodyInstanceParam instance_params;
    param->makeInstanceParam(&instance_params);
    if (instance_params.contact_layer == phys::ContactLayer::SensorCustomReceiver) {
        body->setSensorCustomReceiver(instance_params.receiver_mask, _188[body->isSensor()]);
    } else if (instance_params.groundhit_mask) {
        body->setGroundHitMask(instance_params.contact_layer, instance_params.groundhit_mask);
    } else {
        body->setContactLayerAndGroundHitAndHandler(
            instance_params.contact_layer, instance_params.groundhit, _188[body->isSensor()]);
    }
    body->enableGroundCollision(instance_params.no_hit_ground == 0);
    body->enableWaterCollision(instance_params.no_hit_water == 0);
    body->clearSensorReceiverIgnoredLayer();
}

void* InstanceSet::sub_7100FBBC28(const sead::SafeString& name) const {
    for (auto& rb : mRigidBodySets) {
        void* p = rb.findBodyByHavokName(name);
        if (p != nullptr)
            return p;
    }
    return nullptr;
}

s32 InstanceSet::sub_7100FBBC78(const sead::SafeString& name) const {
    s32 idx = 0;
    for (auto& info : mContactPointInfo) {
        if (name == info.getName())
            return idx;
        idx++;
    }
    return -1;
}

s32 InstanceSet::sub_7100FBBD9C(const sead::SafeString& name) const {
    s32 idx = 0;
    for (auto& info : mCollisionInfo) {
        if (name == info.getName())
            return idx;
        idx++;
    }
    return -1;
}

void InstanceSet::sub_7100FBD284(const sead::Matrix34f& mtx) {
    if (mFlags.isOff(Flag::_1))
        return;

    if (mFlags.isOn(Flag::_80000000)) {
        sub_7100FBC890(mtx, true, false);
    } else {
        mFlags.reset(Flag::_8);
        if (mFlags.isOn(Flag::_2))
            setMtxAndScale(mtx, false, false, mScale);
    }
    mFlags.reset(Flag::_80000000);

    if (mRagdollController == nullptr)
        return;

    if (mRagdollController->sub_7101221CC4() == 0)
        sub_7100FBC890(mtx, false, false);
}

s32 InstanceSet::sub_7100FBDA2C(const sead::SafeString& name) const {
    if (mRagdollBlendWt == nullptr)
        return -1;

    s32 idx = mRagdollBlendWt->findStateIdx(name);
    if (idx >= 0)
        return idx + 2;

    if (name == "full_dynamic") {
        return 1;
    }
    if (name == "full_key_framed") {
        return 0;
    }

    return -1;
}

}  // namespace ksys::phys
