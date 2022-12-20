#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include <Havok/Animation/Animation/Mapper/hkaSkeletonMapper.h>
#include <Havok/Animation/Animation/Rig/hkaPose.h>
#include <Havok/Animation/Physics2012Bridge/Instance/hkaRagdollInstance.h>
#include <Havok/Common/Serialize/Util/hkNativePackfileUtils.h>
#include <Havok/Common/Serialize/Util/hkRootLevelContainer.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/World/hkpPhysicsSystem.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorld.h>
#include <Havok/Physics2012/Utilities/Dynamics/ScaleSystem/hkpSystemScalingUtility.h>
#include <basis/seadRawPrint.h>
#include <gsys/gsysModel.h>
#include <math/seadMathCalcCommon.h>
#include <memory>
#include <resource/seadResource.h>
#include "KingSystem/Physics/Ragdoll/physRagdollInstanceMgr.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "KingSystem/Physics/Rig/physModelBoneAccessor.h"
#include "KingSystem/Physics/Rig/physSkeletonMapper.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/IteratorUtil.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

static u8 sRagdollInstanceUnk1 = 15;
static RagdollInstance::Config sRagdollInstanceConfig;

RagdollInstance::RagdollInstance(SystemGroupHandler* handler)
    : mGroupHandler(handler), _e8(sRagdollInstanceUnk1), _e9(sRagdollInstanceUnk1) {}

RagdollInstance::~RagdollInstance() {
    finalize();
}

bool RagdollInstance::init(const RagdollParam* param, sead::DirectResource* res, gsys::Model* model,
                           sead::Heap* heap) {
    return doInit(param, res, model, heap);
}

bool RagdollInstance::doInit(const RagdollParam* param, sead::DirectResource* res,
                             gsys::Model* model, sead::Heap* heap) {
    if (!res)
        return false;

    // Copy the ragdoll data from the resource and load it in place.
    mRagdollDataSize = res->getRawSize();
    mRagdollData = new (heap, 0x10) u8[mRagdollDataSize];
    std::memcpy(mRagdollData, res->getRawData(), mRagdollDataSize);
    {
        const char* error = nullptr;
        mRootLevelContainer = static_cast<hkRootLevelContainer*>(hkNativePackfileUtils::loadInPlace(
            mRagdollData, static_cast<int>(mRagdollDataSize), nullptr, &error));

        if (!mRootLevelContainer) {
            util::safeDeleteArray(mRagdollData);
            return false;
        }
    }

    mRagdollInstance = mRootLevelContainer->findObject<hkaRagdollInstance>();
    if (!mRagdollInstance)
        return false;

    const hkaSkeleton* skeleton = mRagdollInstance->getSkeleton();
    const int num_bones = skeleton->m_bones.size();

    // Initialise the skeleton mapper or model bone accessor.
    if (mRootLevelContainer->findObject<hkaSkeletonMapper>()) {
        mSkeletonMapper = new (heap) SkeletonMapper;
        auto* skeleton_mapper = mRootLevelContainer->findObject<hkaSkeletonMapper>(nullptr);
        auto* model_skeleton_mapper =
            mRootLevelContainer->findObject<hkaSkeletonMapper>(skeleton_mapper);

        if (!mSkeletonMapper ||
            !mSkeletonMapper->init(skeleton_mapper, model_skeleton_mapper, model, heap)) {
            return false;
        }
    } else {
        mModelBoneAccessor = new (heap) ModelBoneAccessor;
        if (!mModelBoneAccessor->init(skeleton, model, heap)) {
            return false;
        }
    }

    mBoneRigidBodies.allocBufferAssert(num_bones, heap);
    allocateBoneTransforms(num_bones, heap);
    mBoneVectors.allocBufferAssert(num_bones, heap);
    mBoneStuff.allocBufferAssert(num_bones, heap);

    // Create a RagdollRigidBody for each bone.
    for (int i = 0; i < num_bones; ++i) {
        const int parent_bone_idx = getParentOfBone(i) >= 0 ? getParentOfBone(i) : 0;

        EntityCollisionMask mask;
        if (mGroupHandler)
            mask.regular.group_handler_index.SetUnsafe(mGroupHandler->getIndex());
        mask.raw = makeEntityCollisionMask(mContactLayer, mask.raw);
        mask.raw = setEntityCollisionMaskGroundHit(GroundHit::HitAll, mask.raw);
        setBitFields(&mask.raw,  //
                     std::make_pair(mask.regular.ragdoll_bone_index, i),
                     std::make_pair(mask.regular.ragdoll_parent_bone_index, parent_bone_idx),
                     std::make_pair(mask.is_ragdoll, true));

        hkpRigidBody* const hkp_rigid_body = mRagdollInstance->getRigidBodyOfBone(i);
        hkp_rigid_body->setCollisionFilterInfo(mask.raw);

        sead::SafeString bone_name = skeleton->m_bones[i].m_name.cString();
        int separator_index = bone_name.rfindIndex(":");
        if (separator_index >= 0 && separator_index < bone_name.calcLength() - 1)
            bone_name = bone_name.cstr() + separator_index + 1;

        mBoneRigidBodies[i] = new (heap) RagdollRigidBody(bone_name, this, i, hkp_rigid_body, heap);
        if (!mBoneRigidBodies[i]->initMotionAccessorForDynamicMotion(heap))
            return false;
    }

    // Initialise each RagdollRigidBody. This must be done in a separate pass after all
    // bodies have been created because each bone will store references to its neighbours.
    for (int i = 0; i < num_bones; ++i) {
        mBoneRigidBodies[i]->init(heap);
    }

    mTransform = new (heap, alignof(hkQsTransformf))
        hkQsTransformf[1]{hkQsTransformf::IdentityInitializer{}};
    mRagdollParam = param;

    util::PrintDebugFmt("%s %s", sead::SafeString::cEmptyString.cstr(),
                        sead::SafeString::cEmptyString.cstr());

    for (int i = 0, n = mRagdollInstance->m_constraints.size(); i < n; ++i) {
        mRagdollInstance->m_constraints[i]->setPriority(hkpConstraintInstance::PRIORITY_TOI);
    }

    mBoneStuff2.allocBufferAssert(num_bones, heap);
    for (int i = 0; i < num_bones; ++i) {
        // XXX: this is probably an inlined function?
        mBoneStuff2[i] = 0;
        mFlags.set(Flag::_80);
    }

    mModel = model;

    registerSelf();
    return true;
}

void RagdollInstance::allocateBoneTransforms(int num_bones, sead::Heap* heap) {
    static constexpr size_t Alignment = 0x20;
    mBoneTransformsByteSize =
        sead::Mathu::roundUpPow2(sizeof(hkQsTransformf) * num_bones, Alignment);
    auto* buffer = new (heap, Alignment) u8[mBoneTransformsByteSize];
    mBoneTransforms.setBuffer(num_bones, new (buffer) hkQsTransformf[num_bones]);
}

void RagdollInstance::registerSelf() {
    const bool registered = System::instance()->getRagdollInstanceMgr()->addInstance(this);
    mFlags.change(Flag::IsRegistered, registered);
}

void RagdollInstance::unregisterSelf() {
    if (mFlags.isOn(Flag::IsRegistered)) {
        System::instance()->getRagdollInstanceMgr()->removeInstance(this);
        mFlags.reset(Flag::IsRegistered);
    }
}

void RagdollInstance::finalize() {
    for (auto body : util::indexIter(mBoneRigidBodies)) {
        body.get()->setCollisionInfo(nullptr);
        body.get()->setContactPointInfo(nullptr);
    }

    if (isAddedToWorld())
        removeFromWorldImmediately();

    if (mRagdollInstance != nullptr)
        removeConstraints();

    for (auto body : util::indexIter(mBoneRigidBodies))
        delete body.get();

    mBoneRigidBodies.freeBuffer();

    if (mSkeletonMapper)
        util::safeDelete(mSkeletonMapper);

    if (mModelBoneAccessor)
        util::safeDelete(mModelBoneAccessor);

    if (mRagdollData) {
        hkNativePackfileUtils::unloadInPlace(mRagdollData, static_cast<int>(mRagdollDataSize));
        delete[] mRagdollData;
        mRagdollData = nullptr;
        mRootLevelContainer = nullptr;
        mRagdollInstance = nullptr;
    }

    if (mTransform)
        util::safeDeleteArray(mTransform);

    mBoneVectors.freeBuffer();
    mBoneStuff.freeBuffer();
    mBoneStuff2.freeBuffer();

    if (mBoneTransformsByteSize != 0) {
        std::destroy_n(mBoneTransforms.getBufferPtr(), mBoneTransforms.size());
        delete[] reinterpret_cast<u8*>(mBoneTransforms.getBufferPtr());
        mBoneTransformsByteSize = 0;
    }
}

void RagdollInstance::removeConstraints() {
    for (int i = 0, n = mRagdollInstance->m_constraints.getSize(); i < n; ++i) {
        auto* constraint = mRagdollInstance->m_constraints[i];
        if (constraint->getOwner() != nullptr) {
            auto* world = System::instance()->getHavokWorld(ContactLayerType::Entity);
            world->removeConstraint(constraint);
        }
    }
}

bool RagdollInstance::isAddedToWorld() const {
    return mBoneRigidBodies.size() > 0 && mBoneRigidBodies.back()->isAddedToWorld();
}

void RagdollInstance::removeFromWorldImmediately() {
    ScopedPhysicsLock lock{this};

    removeConstraints();
    for (auto body : util::indexIter(mBoneRigidBodies))
        body.get()->removeFromWorldImmediately();
}

void RagdollInstance::removeFromWorld() {
    for (auto body : util::indexIter(mBoneRigidBodies))
        body.get()->removeFromWorld();
}

bool RagdollInstance::removeFromWorldAndResetLinks() {
    bool removed = true;
    for (auto body : util::indexIter(mBoneRigidBodies))
        removed &= body.get()->removeFromWorldAndResetLinks();

    unregisterSelf();

    return removed;
}

bool RagdollInstance::isAddingToWorld() const {
    return mBoneRigidBodies.size() > 0 && mBoneRigidBodies.back()->isAddingBodyToWorld();
}

void RagdollInstance::setTransform(const sead::Matrix34f& transform) {
    hkQsTransformf hk_transform;
    toHkQsTransform(&hk_transform, transform, sead::Vector3f::ones);
    setTransform(hk_transform);
}

void RagdollInstance::setTransform(const hkQsTransformf& transform) {
    ScopedPhysicsLock lock{this};

    if (mSkeletonMapper)
        mSkeletonMapper->mapPoseA();

    mRagdollInstance->setPoseModelSpace(
        getBoneAccessor()->getPose()->getSyncedPoseModelSpace().data(), transform);

    if (mExtraRigidBody) {
        sead::Matrix34f old_transform;
        mBoneRigidBodies[mBoneIndexForExtraRigidBody]->getTransform(&old_transform);
        mExtraRigidBody->setTransform(old_transform);

        if (mGroupHandler) {
            mExtraRigidBody->setCollisionFilterInfo(
                mGroupHandler->makeRagdollCollisionFilterInfo(GroundHit::HitAll));
        }
    }
}

void RagdollInstance::setScale(float scale) {
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

            mBoneRigidBodies[i]->updateShape();
        }
    }

    if (mSkeletonMapper)
        mSkeletonMapper->getBoneAccessor().setScale(scale);
}

void RagdollInstance::setFixedAndPreserveImpulse(Fixed fixed,
                                                 MarkLinearVelAsDirty mark_linear_vel_as_dirty) {
    for (auto* body : mBoneRigidBodies)
        body->setFixedAndPreserveImpulse(fixed, mark_linear_vel_as_dirty);
}

void RagdollInstance::resetFrozenState() {
    for (auto* body : mBoneRigidBodies)
        body->resetFrozenState();
}

void RagdollInstance::setUseSystemTimeFactor(bool use) {
    for (auto* body : mBoneRigidBodies)
        body->setUseSystemTimeFactor(use);
}

void RagdollInstance::clearFlag400000(bool clear) {
    for (auto* body : mBoneRigidBodies)
        body->clearFlag400000(clear);
}

void RagdollInstance::setEntityMotionFlag200(bool set) {
    for (auto* body : mBoneRigidBodies)
        body->setEntityMotionFlag200(set);
}

void RagdollInstance::setFixed(Fixed fixed, PreserveVelocities preserve_velocities) {
    for (auto* body : mBoneRigidBodies)
        body->setFixed(fixed, preserve_velocities);
}

ModelBoneAccessor* RagdollInstance::getModelBoneAccessor() const {
    if (mSkeletonMapper)
        return &mSkeletonMapper->getModelBoneAccessor();

    return mModelBoneAccessor;
}

void RagdollInstance::m3() {}

void RagdollInstance::setUserTag(UserTag* tag) {
    for (auto* body : mBoneRigidBodies)
        body->setUserTag(tag);
}

void RagdollInstance::setSystemGroupHandler(SystemGroupHandler* handler) {
    for (auto* body : mBoneRigidBodies)
        body->setSystemGroupHandler(handler);

    mGroupHandler = handler;
}

void RagdollInstance::setContactPointInfo(ContactPointInfo* info) {
    for (auto* body : mBoneRigidBodies)
        body->setContactPointInfo(info);
}

void RagdollInstance::enableContactLayer(ContactLayer layer) {
    for (auto* body : mBoneRigidBodies)
        body->enableContactLayer(layer, false);
}

void RagdollInstance::disableContactLayer(ContactLayer layer) {
    for (auto* body : mBoneRigidBodies)
        body->disableContactLayer(layer, false);
}

void RagdollInstance::setContactAll() {
    for (auto* body : mBoneRigidBodies)
        body->setContactAll(false);
}

void RagdollInstance::setContactNone() {
    for (auto* body : mBoneRigidBodies)
        body->setContactNone(false);
}

void RagdollInstance::setContactAll(int bone_index) {
    mBoneRigidBodies[bone_index]->setContactAll(false);
}

void RagdollInstance::setContactNone(int bone_index) {
    mBoneRigidBodies[bone_index]->setContactNone(false);
}

void RagdollInstance::changeWorldState(RagdollInstance::WorldState state) {
    if (getWorldState() == state)
        return;

    const int num_rigid_bodies = mRagdollInstance->m_rigidBodies.size();

    ScopedPhysicsLock lock{this};

    if (state == WorldState::AddedToWorld) {
        if (mModel) {
            if (auto* accessor = getModelBoneAccessor())
                accessor->copyModelPoseToHavok(ModelBoneAccessor::EnableScale::No);

            setTransform(mModel->getMatrix());
        }

        for (int i = 0, n = num_rigid_bodies; i < n; ++i) {
            mBoneRigidBodies[i]->addToWorld();

            mBoneRigidBodies[i]->setLinearVelocity(sead::Vector3f::zero);
            mBoneRigidBodies[i]->setAngularVelocity(sead::Vector3f::zero);

            if (mKeyframedBones.isOnBit(i)) {
                mBoneRigidBodies[i]->changeMotionType(MotionType::Keyframed);
                mBoneRigidBodies[i]->setContactLayer(ContactLayer::EntityNoHit);
            } else {
                mBoneRigidBodies[i]->changeMotionType(MotionType::Dynamic);
                mBoneRigidBodies[i]->setContactLayer(mContactLayer);
            }
        }

        for (auto& x : mBoneStuff)
            x = 1;

        mFlags.reset(Flag::_8);
        _e8 = _e9;

        for (auto* body : mBoneRigidBodies)
            body->setContactNone(true);

        mFlags.set(Flag::_20);
        mFlags.set(Flag::AddedToWorld);
        mFlags.reset(Flag::_40);
        mFlags.reset(Flag::_2);
        mFlags.reset(Flag::_4);
    } else {
        for (int i = 0, n = num_rigid_bodies; i < n; ++i)
            mBoneRigidBodies[i]->removeFromWorld();

        mFlags.reset(Flag::AddedToWorld);
        mFlags.reset(Flag::_40);
    }
}

RagdollInstance::WorldState RagdollInstance::getWorldState() const {
    return mFlags.isOn(Flag::AddedToWorld) ? WorldState::AddedToWorld : WorldState::NotAddedToWorld;
}

void RagdollInstance::setExtraRigidBody(RigidBody* body, int bone_index) {
    mExtraRigidBody = body;
    mBoneIndexForExtraRigidBody = bone_index;
}

void RagdollInstance::setGravityFactor(float factor) {
    for (auto* body : mBoneRigidBodies)
        body->setGravityFactor(factor);
}

RagdollRigidBody* RagdollInstance::getBoneRigidBodyByName(const sead::SafeString& name) const {
    const int index = getBoneIndexByName(name);
    if (index < 0)
        return nullptr;

    return mBoneRigidBodies[index];
}

int RagdollInstance::getBoneIndexByModelKey(const gsys::BoneAccessKey& key) const {
    const int model_bone_index = getModelBoneAccessor()->findBoneIndex(key);

    const char* bone_name = getModelBoneAccessor()->getBoneName(model_bone_index);
    if (bone_name == nullptr)
        return -1;

    return getBoneIndexByName(sead::FormatFixedSafeString<256>("Ragdoll_%s", bone_name));
}

int RagdollInstance::getBoneIndexByName(const sead::SafeString& name) const {
    int index = 0;
    for (auto* body : mBoneRigidBodies) {
        if (name == body->getHkBodyName())
            return index;
        ++index;
    }
    return -1;
}

int RagdollInstance::getParentOfBone(int index) const {
    return mRagdollInstance->getParentOfBone(index);
}

RagdollRigidBody* RagdollInstance::getParentBoneRigidBody(const RigidBody* body) const {
    return sead::DynamicCast<const RagdollRigidBody>(body)->getParentBody_();
}

int RagdollInstance::getNumChildBones(const RigidBody* body) const {
    return sead::DynamicCast<const RagdollRigidBody>(body)->getChildBodies_().size();
}

RagdollRigidBody* RagdollInstance::getChildBoneRigidBody(const RigidBody* body, int index) const {
    return sead::DynamicCast<const RagdollRigidBody>(body)->getChildBodies_()[index];
}

sead::Matrix34f RagdollInstance::getTransform(int bone_index) const {
    if (mFlags.isOff(Flag::_40)) {
        if (util::isMatrixInvalid(mModel->getMatrix()))
            return sead::Matrix34f::ident;

        return mModel->getMatrix();
    }

    const sead::Matrix34f parent_transform = mBoneRigidBodies[bone_index]->getTransform();
    hkQsTransformf hk_parent_transform;
    toHkQsTransform(&hk_parent_transform, parent_transform, sead::Vector3f::ones);

    hkQsTransformf result;
    result.setMulMulInverse(hk_parent_transform, mBoneTransforms[bone_index]);

    const bool parent_ok = hk_parent_transform.isOk();
    SEAD_ASSERT(parent_ok);
    const bool bone_ok = mBoneTransforms[bone_index].isOk();
    SEAD_ASSERT(bone_ok);
    const bool result_ok = result.isOk();
    SEAD_ASSERT(result_ok);

    sead::Matrix34f out;
    toMtx34(&out, result);
    return out;
}

sead::Matrix34f RagdollInstance::getTransformWithCustomYAxis(int bone_index,
                                                             const sead::Vector3f& y_axis) const {
    if (mFlags.isOff(Flag::_40)) {
        if (util::isMatrixInvalid(mModel->getMatrix()))
            return sead::Matrix34f::ident;

        return mModel->getMatrix();
    }

    sead::Matrix34f transform = mBoneRigidBodies[bone_index]->getTransform();

    {
        sead::Vector3f v1 = (transform(1, 1) > 0.0f) ? y_axis : -y_axis;
        v1.normalize();

        sead::Vector3f c2 = util::getCol(transform, 2);
        c2.normalize();

        sead::Vector3f v0;
        // Compute the cross product of v1 and c2.
        // If v1 and c2 are collinear, then their cross product will be the zero vector;
        // compute the cross product of v1 and the first column instead in that case.
        // (That product should never be zero because the first column and u2 are not collinear.)
        const auto dot = sead::Mathf::abs(v1.dot(c2));
        // XXX: this should probably check if the dot product is approximately equal to 1.0 instead
        v0.setCross(v1, dot >= 1.0f ? util::getCol(transform, 0) : c2);
        v0.normalize();

        sead::Vector3f v2;
        v2.setCross(v0, v1);
        v2.normalize();

        transform.setBase(0, v0);
        transform.setBase(1, v1);
        transform.setBase(2, v2);
    }

    hkQsTransformf hk_parent_transform;
    toHkQsTransform(&hk_parent_transform, transform, sead::Vector3f::ones);

    hkQsTransformf result;
    result.setMulMulInverse(hk_parent_transform, mBoneTransforms[bone_index]);

    const bool parent_ok = hk_parent_transform.isOk();
    SEAD_ASSERT(parent_ok);
    const bool bone_ok = mBoneTransforms[bone_index].isOk();
    SEAD_ASSERT(bone_ok);
    const bool result_ok = result.isOk();
    SEAD_ASSERT(result_ok);

    sead::Matrix34f out;
    toMtx34(&out, result);
    return out;
}

int RagdollInstance::getConstraintIndexByName(const sead::SafeString& name) const {
    for (int i = 0, n = getNumConstraints(); i < n; ++i) {
        if (name == mRagdollInstance->m_constraints[i]->getName())
            return i;
    }
    return -1;
}

int RagdollInstance::getNumConstraints() const {
    return mRagdollInstance->m_constraints.size();
}

void RagdollInstance::enableConstraint(int index, bool enable) {
    mDisabledConstraints.changeBit(index, !enable);
}

bool RagdollInstance::isConstraintEnabled(int index) const {
    return mDisabledConstraints.isOffBit(index);
}

void RagdollInstance::setContactLayer(ContactLayer layer) {
    if (mContactLayer.value() == layer)
        return;

    if (mFlags.isOn(Flag::AddedToWorld)) {
        for (int bone = 0, num_bones = mBoneRigidBodies.size(); bone < num_bones; ++bone) {
            if (mKeyframedBones.isOffBit(bone))
                mBoneRigidBodies[bone]->setContactLayer(layer);
        }
    }

    mContactLayer = layer;
}

void RagdollInstance::setKeyframed(int bone_index, bool keyframed,
                                   SyncToThisBone sync_to_this_bone) {
    mKeyframedBones.changeBit(bone_index, keyframed);

    if (keyframed) {
        mBoneRigidBodies[bone_index]->setContactLayer(ContactLayer::EntityNoHit);
        mBoneRigidBodies[bone_index]->changeMotionType(MotionType::Keyframed);
    } else {
        mBoneRigidBodies[bone_index]->setContactLayer(mContactLayer);
        mBoneRigidBodies[bone_index]->changeMotionType(MotionType::Dynamic);
    }

    mKeyframedBonesToSyncTo.changeBit(bone_index, keyframed && bool(sync_to_this_bone));
}

void RagdollInstance::setUnk1(u8 value) {
    value = sead::Mathi::clamp(value, 0, sRagdollInstanceUnk1);
    _e9 = value;
    _e8 = value;
}

void RagdollInstance::setMaximumUnk1(u8 value) {
    sRagdollInstanceUnk1 = value;
}

void RagdollInstance::stopForcingKeyframing() {
    if (mFlags.isOn(Flag::AddedToWorld)) {
        for (int i = 0, n = mBoneRigidBodies.size(); i < n; ++i) {
            setKeyframed(i, false, {});
        }
    } else {
        mKeyframedBones.makeAllZero();
        mKeyframedBonesToSyncTo.makeAllZero();
    }
}

void RagdollInstance::update() {
    if (!isAddedToWorld()) {
        for (int i = 0, n = getNumConstraints(); i < n; ++i) {
            auto* constraint = mRagdollInstance->m_constraints[i];
            if (constraint->getOwner() != nullptr) {
                System::instance()
                    ->getHavokWorld(ContactLayerType::Entity)
                    ->removeConstraint(constraint);
            }
        }
        return;
    }

    for (int i = 0, n = getNumConstraints(); i < n; ++i) {
        auto* constraint = mRagdollInstance->m_constraints[i];
        if (constraint->getOwner() == nullptr) {
            System::instance()->getHavokWorld(ContactLayerType::Entity)->addConstraint(constraint);
        }

        const bool should_enable = mDisabledConstraints.isOffBit(i);
        if (should_enable != constraint->isEnabled()) {
            if (should_enable) {
                constraint->setPriority(getConfig().priority);
                constraint->enable();
            } else {
                constraint->setPriority(hkpConstraintInstance::PRIORITY_PSI);
                constraint->disable();
            }
        }
    }

    updateGravityFactorOverride();
}

RagdollInstance::Config& RagdollInstance::getConfig() {
    return sRagdollInstanceConfig;
}

void RagdollInstance::updateGravityFactorOverride() {
    if (mFlags.isOff(Flag::_200))
        return;

    if (System::instance() == nullptr)
        return;

    const float factor_divisor = System::instance()->get6c();
    for (int i = 0, n = mBoneRigidBodies.size(); i < n; ++i) {
        mBoneRigidBodies[i]->setGravityFactor(mGravityFactorOverride / factor_divisor);
    }
}

RagdollInstance::ScopedPhysicsLock::ScopedPhysicsLock(const RagdollInstance* instance)
    : mInstance{instance}, mWorldLock{instance->isAddedToWorld(), ContactLayerType::Entity} {
    for (auto body : util::indexIter(instance->mBoneRigidBodies))
        body.get()->lock(RigidBody::AlsoLockWorld::No);
}

RagdollInstance::ScopedPhysicsLock::~ScopedPhysicsLock() {
    for (auto body : util::indexIter(mInstance->mBoneRigidBodies))
        body.get()->unlock(RigidBody::AlsoLockWorld::No);
}

BoneAccessor* RagdollInstance::getBoneAccessor() const {
    if (mSkeletonMapper)
        return &mSkeletonMapper->getBoneAccessor();

    return mModelBoneAccessor;
}

}  // namespace ksys::phys
