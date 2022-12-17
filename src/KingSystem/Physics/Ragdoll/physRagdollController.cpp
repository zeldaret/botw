#include "KingSystem/Physics/Ragdoll/physRagdollController.h"
#include <Havok/Animation/Animation/Rig/hkaPose.h>
#include <Havok/Animation/Physics2012Bridge/Instance/hkaRagdollInstance.h>
#include <Havok/Common/Serialize/Util/hkNativePackfileUtils.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/World/hkpPhysicsSystem.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorld.h>
#include <Havok/Physics2012/Utilities/Dynamics/ScaleSystem/hkpSystemScalingUtility.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/Ragdoll/physRagdollControllerMgr.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "KingSystem/Physics/Rig/physModelBoneAccessor.h"
#include "KingSystem/Physics/Rig/physSkeletonMapper.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/IteratorUtil.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

static u8 sUnk1 = 15;

void RagdollController::setUnk1(u8 value) {
    sUnk1 = value;
}

RagdollController::RagdollController(SystemGroupHandler* handler)
    : mGroupHandler(handler), _e8(sUnk1), _e9(sUnk1) {}

RagdollController::~RagdollController() {
    finalize();
}

void RagdollController::finalize() {
    for (auto body : util::indexIter(mRigidBodies)) {
        body.get()->setCollisionInfo(nullptr);
        body.get()->setContactPointInfo(nullptr);
    }

    if (isAddedToWorld())
        removeFromWorldImmediately();

    if (mRagdollInstance != nullptr)
        removeConstraints();

    for (auto body : util::indexIter(mRigidBodies))
        delete body.get();

    mRigidBodies.freeBuffer();

    if (mSkeletonMapper)
        util::safeDelete(mSkeletonMapper);

    if (mModelBoneAccessor)
        util::safeDelete(mModelBoneAccessor);

    if (mRawRagdollData) {
        hkNativePackfileUtils::unloadInPlace(mRawRagdollData, mRawRagdollDataSize);
        delete[] mRawRagdollData;
        mRawRagdollData = nullptr;
        mRootLevelContainer = nullptr;
        mRagdollInstance = nullptr;
    }

    if (mRotations)
        util::safeDeleteArray(mRotations);

    mBoneVectors.freeBuffer();
    mBoneStuff.freeBuffer();
    mBones.freeBuffer();

    if (_b0) {
        delete[] _a8;
        _b0 = 0;
    }
}

void RagdollController::removeConstraints() {
    for (int i = 0, n = mRagdollInstance->m_constraints.getSize(); i < n; ++i) {
        auto* constraint = mRagdollInstance->m_constraints[i];
        if (constraint->getOwner() != nullptr) {
            auto* world = System::instance()->getHavokWorld(ContactLayerType::Entity);
            world->removeConstraint(constraint);
        }
    }
}

bool RagdollController::isAddedToWorld() const {
    return mRigidBodies.size() > 0 && mRigidBodies.back()->isAddedToWorld();
}

void RagdollController::removeFromWorldImmediately() {
    ScopedPhysicsLock lock{this};

    removeConstraints();
    for (auto body : util::indexIter(mRigidBodies))
        body.get()->removeFromWorldImmediately();
}

void RagdollController::removeFromWorld() {
    for (auto body : util::indexIter(mRigidBodies))
        body.get()->removeFromWorld();
}

bool RagdollController::removeFromWorldAndResetLinks() {
    bool removed = true;
    for (auto body : util::indexIter(mRigidBodies))
        removed &= body.get()->removeFromWorldAndResetLinks();

    if (mFlags.isOn(Flag::IsRegistered)) {
        System::instance()->getRagdollControllerMgr()->removeController(this);
        mFlags.reset(Flag::IsRegistered);
    }

    return removed;
}

bool RagdollController::isAddingToWorld() const {
    return mRigidBodies.size() > 0 && mRigidBodies.back()->isAddingBodyToWorld();
}

void RagdollController::setTransform(const sead::Matrix34f& transform) {
    hkQsTransformf hk_transform;
    toHkQsTransform(&hk_transform, transform, sead::Vector3f::ones);
    setTransform(hk_transform);
}

void RagdollController::setTransform(const hkQsTransformf& transform) {
    ScopedPhysicsLock lock{this};

    if (mSkeletonMapper)
        mSkeletonMapper->mapPoseA();

    mRagdollInstance->setPoseModelSpace(
        getBoneAccessor()->getPose()->getSyncedPoseModelSpace().data(), transform);

    if (mExtraRigidBody) {
        sead::Matrix34f old_transform;
        mRigidBodies[mRigidBodyIndex]->getTransform(&old_transform);
        mExtraRigidBody->setTransform(old_transform);

        if (mGroupHandler) {
            mExtraRigidBody->setCollisionFilterInfo(
                mGroupHandler->makeRagdollCollisionFilterInfo(GroundHit::HitAll));
        }
    }
}

void RagdollController::setScale(float scale) {
    if (sead::Mathf::equalsEpsilon(scale, 1.0))
        return;

    {
        ScopedPhysicsLock lock{this};

        const hkVector4 translation =
            mRagdollInstance->getRigidBodyOfBone(0)->getTransform().getTranslation();

        // Construct a system with all the rigid bodies and constraints, then scale it.
        hkpPhysicsSystem system;

        const int num_bodies = mRagdollInstance->getRigidBodyArray().size();
        for (int i = 0; i < num_bodies; ++i) {
            hkpRigidBody* body = mRagdollInstance->getRigidBodyArray()[i];

            // Fix the positions to be in model space.
            hkVector4f pos;
            pos.setSub(body->getTransform().getTranslation(), translation);
            body->setPosition(pos);

            system.addRigidBody(body);
        }

        for (int i = 0, n = mRagdollInstance->getConstraintArray().size(); i < n; ++i) {
            system.addConstraint(mRagdollInstance->getConstraintArray()[i]);
        }

        hkpSystemScalingUtility::scaleSystem(&system, scale);

        for (int i = 0; i < num_bodies; ++i) {
            hkpRigidBody* body = mRagdollInstance->getRigidBodyArray()[i];

            // Fix the positions to be in world space.
            hkVector4f pos;
            pos.setAdd(body->getTransform().getTranslation(), translation);
            body->setPosition(pos);

            mRigidBodies[i]->updateShape();
        }
    }

    if (mSkeletonMapper)
        mSkeletonMapper->getBoneAccessor().setScale(scale);
}

void RagdollController::setFixedAndPreserveImpulse(Fixed fixed,
                                                   MarkLinearVelAsDirty mark_linear_vel_as_dirty) {
    for (auto* body : mRigidBodies)
        body->setFixedAndPreserveImpulse(fixed, mark_linear_vel_as_dirty);
}

void RagdollController::resetFrozenState() {
    for (auto* body : mRigidBodies)
        body->resetFrozenState();
}

void RagdollController::setUseSystemTimeFactor(bool use) {
    for (auto* body : mRigidBodies)
        body->setUseSystemTimeFactor(use);
}

void RagdollController::clearFlag400000(bool clear) {
    for (auto* body : mRigidBodies)
        body->clearFlag400000(clear);
}

void RagdollController::setEntityMotionFlag200(bool set) {
    for (auto* body : mRigidBodies)
        body->setEntityMotionFlag200(set);
}

void RagdollController::setFixed(Fixed fixed, PreserveVelocities preserve_velocities) {
    for (auto* body : mRigidBodies)
        body->setFixed(fixed, preserve_velocities);
}

BoneAccessor* RagdollController::getModelBoneAccessor() const {
    if (mSkeletonMapper)
        return &mSkeletonMapper->getModelBoneAccessor();

    return mModelBoneAccessor;
}

void RagdollController::m3() {}

void RagdollController::setUserTag(UserTag* tag) {
    for (auto* body : mRigidBodies)
        body->setUserTag(tag);
}

void RagdollController::setSystemGroupHandler(SystemGroupHandler* handler) {
    for (auto* body : mRigidBodies)
        body->setSystemGroupHandler(handler);
}

void RagdollController::setContactPointInfo(ContactPointInfo* info) {
    for (auto* body : mRigidBodies)
        body->setContactPointInfo(info);
}

int RagdollController::getParentOfBone(int index) const {
    return mRagdollInstance->getParentOfBone(index);
}

RagdollController::ScopedPhysicsLock::ScopedPhysicsLock(const RagdollController* ctrl)
    : mCtrl{ctrl}, mWorldLock{ctrl->isAddedToWorld(), ContactLayerType::Entity} {
    for (auto body : util::indexIter(ctrl->mRigidBodies))
        body.get()->lock(RigidBody::AlsoLockWorld::No);
}

RagdollController::ScopedPhysicsLock::~ScopedPhysicsLock() {
    for (auto body : util::indexIter(mCtrl->mRigidBodies))
        body.get()->unlock(RigidBody::AlsoLockWorld::No);
}

BoneAccessor* RagdollController::getBoneAccessor() const {
    if (mSkeletonMapper)
        return &mSkeletonMapper->getBoneAccessor();

    return mModelBoneAccessor;
}

}  // namespace ksys::phys
