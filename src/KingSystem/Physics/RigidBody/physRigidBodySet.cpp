#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::phys {

RigidBodySet::RigidBodySet(const sead::SafeString& name) : mName(name) {}

RigidBodySet::~RigidBodySet() {
    util::PrintDebug("~RigidBodySet");
}

void RigidBodySet::setFixedAndPreserveImpulse(bool fixed, bool mark_linear_vel_as_dirty) {
    for (auto& body : mRigidBodies)
        body.setFixedAndPreserveImpulse(fixed, mark_linear_vel_as_dirty);
}

void RigidBodySet::resetFrozenState() {
    for (auto& body : mRigidBodies)
        body.resetFrozenState();
}

void RigidBodySet::setUseSystemTimeFactor(bool use) {
    for (auto& body : mRigidBodies)
        body.setUseSystemTimeFactor(use);
}

void RigidBodySet::clearFlag400000(bool clear) {
    for (auto& body : mRigidBodies)
        body.setFlag400000(!clear);
}

void RigidBodySet::setEntityMotionFlag200(bool set) {
    for (auto& body : mRigidBodies)
        body.setEntityMotionFlag200(set);
}

void RigidBodySet::setFixed(bool fixed, bool preserve_velocities) {
    for (auto& body : mRigidBodies)
        body.setFixed(fixed, preserve_velocities);
}

void RigidBodySet::updateMotionTypeRelatedFlags() {
    for (auto& body : mRigidBodies)
        body.updateMotionTypeRelatedFlags();
}

void RigidBodySet::triggerScheduledMotionTypeChange() {
    for (auto& body : mRigidBodies)
        body.triggerScheduledMotionTypeChange();
}

bool RigidBodySet::hasActiveEntityBody() const {
    for (const auto& body : mRigidBodies) {
        if (body.isEntity() && body.isActive())
            return true;
    }
    return false;
}

RigidBody* RigidBodySet::findBodyByHavokName(const sead::SafeString& name) {
    const int index = findBodyIndexByHavokName(name);
    if (index < 0)
        return nullptr;
    return mRigidBodies[index];
}

const RigidBody* RigidBodySet::findBodyByHavokName(const sead::SafeString& name) const {
    const int index = findBodyIndexByHavokName(name);
    if (index < 0)
        return nullptr;
    return mRigidBodies[index];
}

int RigidBodySet::findBodyIndexByHavokName(const sead::SafeString& name) const {
    int idx = 0;
    for (const auto& body : mRigidBodies) {
        if (name == body.getHkBodyName())
            return idx;
        ++idx;
    }
    return -1;
}

void RigidBodySet::setUserTag(UserTag* tag) {
    for (auto& body : mRigidBodies)
        body.setUserTag(tag);
}

void RigidBodySet::setSystemGroupHandler(SystemGroupHandler* handler) {
    for (auto& body : mRigidBodies) {
        if (handler == nullptr || handler->getLayerType() == body.getLayerType())
            body.setSystemGroupHandler(handler);
    }
}

void RigidBodySet::setSystemGroupHandler(SystemGroupHandler* handler, ContactLayerType layer_type) {
    if (handler != nullptr && handler->getLayerType() != layer_type)
        return;

    for (auto& body : mRigidBodies) {
        if (body.getLayerType() == layer_type)
            body.setSystemGroupHandler(handler);
    }
}

void RigidBodySet::setTransform(const sead::Matrix34f& mtx) {
    for (auto& body : mRigidBodies)
        body.setTransform(mtx, true);
}

void RigidBodySet::enableContactLayer(ContactLayer layer) {
    const auto type = getContactLayerType(layer);
    for (auto& body : mRigidBodies) {
        if (body.getLayerType() == type)
            body.enableContactLayer(layer);
    }
}

void RigidBodySet::disableContactLayer(ContactLayer layer) {
    const auto type = getContactLayerType(layer);
    for (auto& body : mRigidBodies) {
        if (body.getLayerType() == type)
            body.disableContactLayer(layer);
    }
}

void RigidBodySet::disableAllContactLayers() {
    for (auto& body : mRigidBodies)
        body.setContactNone();
}

void RigidBodySet::setScaleAndUpdateImmediately(float scale) {
    for (auto it = mRigidBodies.begin(), end = mRigidBodies.end(); it != end; ++it) {
        it->setUpdateRequestedFlag();
        it->setScale(scale);
        it->processUpdateRequests(nullptr, nullptr);
    }
}

void RigidBodySet::setScale(float scale) {
    for (auto& body : mRigidBodies)
        body.setScale(scale);
}

void RigidBodySet::addToWorld() {
    for (auto& body : mRigidBodies)
        body.addToWorld();
}

void RigidBodySet::removeFromWorld() {
    for (auto& body : mRigidBodies)
        body.removeFromWorld();
}

bool RigidBodySet::removeFromWorldAndResetLinks() {
    bool ok = true;
    for (auto& body : mRigidBodies)
        ok &= body.removeFromWorldAndResetLinks();
    return ok;
}

bool RigidBodySet::hasNoRigidBodyWithFlag8(bool require_motion_flag_1_to_be_unset) {
    for (auto it = mRigidBodies.begin(), end = mRigidBodies.end(); it != end; ++it) {
        if (it->isAddedToWorld())
            return false;
        if (require_motion_flag_1_to_be_unset && it->isAddingBodyToWorld())
            return false;
    }
    return true;
}

void RigidBodySet::callRigidBody_x_7(u8 type) {
    for (auto& body : mRigidBodies)
        body.x_17(type);
}

}  // namespace ksys::phys
