#include "KingSystem/Physics/physInstanceSet.h"

namespace ksys::phys {

void InstanceSet::setFlag2() {
    mFlags.set(Flag::_2);
    if (_d8 != nullptr) {
        mFlags.set(Flag::_2);
        mFlags.set(Flag::disableDraw);
    }
}

void InstanceSet::clothVisibleStuff() {
    if (_d8 != nullptr) {
        mFlags.set(Flag::disableDraw);
    }
}

void InstanceSet::setInDemo() {
    mFlags.set(Flag::inDemo);
}

void InstanceSet::resetInDemo() {
    mFlags.reset(Flag::inDemo);
}

void InstanceSet::clothVisibleStuff_0(s32 setting) {
    if (mFlags.isOn(Flag::inDemo))
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
        rb.sub_7100FA97FC();
    }

    for (auto& body : mList) {
        body->sub_7100F8CFA0();
    }

    if (mCollisionController != nullptr)
        mCollisionController->sub_7100F5EC30();
}

void InstanceSet::sub_7100FBACE0(phys::ContactLayer layer) {
    bool sensor = phys::isSensorLayer(layer);

    for (auto& rb : mRigidBodySets) {
        rb.disableCollisionMaybe(layer);
    }
    if (sensor)
        return;

    if (mRagdollController != nullptr)
        mRagdollController->sub_7101221728(layer);

    if (mCollisionController != nullptr)
        mCollisionController->enableCollisionMaybe_0(layer);
}

void InstanceSet::sub_7100FBAD74() {
    for (auto& rb : mRigidBodySets) {
        rb.disableAllContact();
    }
    if (mRagdollController != nullptr) {
        mRagdollController->sub_71012217A8();
    }
    if (mCollisionController != nullptr) {
        mCollisionController->sub_7100F60604();
    }
}

void* InstanceSet::sub_7100FBAEDC(s32 idx1, s32 idx2) const {
    if (mRigidBodySets.size() <= idx1)
        return nullptr;
    return mRigidBodySets[idx1]->getRigidBody(idx2);
}

// NON_MATCHING
void InstanceSet::sub_7100FBB00C(phys::RigidBody* body, phys::RigidBodyParam* param) {
    if (body == nullptr)
        return;

    phys::RigidBodyParamView view;
    param->getParams(&view);
    if (view.contact_layer == phys::ContactLayer::SensorCustomReceiver) {
        body->sub_7100F8F9E8(&view.flags, _188[body->isMassScaling()]);
    } else if (view.info_5e0) {
        body->sub_7100F8FA44(view.contact_layer, view.info_5e0);
    } else {
        body->sub_7100F8F8CC(view.contact_layer, view.groundhit, _188[body->isMassScaling()]);
    }
    body->setCollideGround(view.no_hit_ground == 0);
    body->setCollideWater(view.no_hit_water == 0);
    body->sub_7100F8F51C();
}

void* InstanceSet::sub_7100FBBC28(const sead::SafeString& name) const {
    for (auto& rb : mRigidBodySets) {
        void* p = rb.findXByName(name);
        if (p != nullptr)
            return p;
    }
    return nullptr;
}

s32 InstanceSet::sub_7100FBBC78(const sead::SafeString& name) const {
    s32 idx = 0;
    for (auto& info : mContactInfos) {
        if (name == info.mName)
            return idx;
        idx++;
    }
    return -1;
}

s32 InstanceSet::sub_7100FBBD9C(const sead::SafeString& name) const {
    s32 idx = 0;
    for (auto& info : mCollisionInfos) {
        if (name == info.mName)
            return idx;
        idx++;
    }
    return -1;
}

void InstanceSet::sub_7100FBD284(sead::Matrix34f* mtx) {
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
