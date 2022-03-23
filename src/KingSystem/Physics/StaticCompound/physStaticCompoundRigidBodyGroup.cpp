#include "KingSystem/Physics/StaticCompound/physStaticCompoundRigidBodyGroup.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/World/hkpPhysicsSystem.h>
#include <Havok/Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyFromResource.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundInfo.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Utils/MathUtil.h"

namespace ksys::phys {

// TODO: rename
constexpr int BodyGroupNumMatrices = 8;

static StaticCompoundRigidBodyGroup::Config sScRigidBodyGroupConfig;
static StaticCompoundRigidBodyGroup::Epsilons sScRigidBodyGroupEpsilons;

StaticCompoundRigidBodyGroup::Config& StaticCompoundRigidBodyGroup::getConfig() {
    return sScRigidBodyGroupConfig;
}

StaticCompoundRigidBodyGroup::Epsilons& StaticCompoundRigidBodyGroup::getEpsilons() {
    return sScRigidBodyGroupEpsilons;
}

StaticCompoundRigidBodyGroup::StaticCompoundRigidBodyGroup() = default;

StaticCompoundRigidBodyGroup::~StaticCompoundRigidBodyGroup() {
    mFlags.reset(Flag::Initialised);

    for (int i = 0, n = mRigidBodiesPerBodyLayerType.size(); i < n; ++i) {
        delete mRigidBodiesPerBodyLayerType[i];
    }

    mRigidBodiesPerBodyLayerType.freeBuffer();
    mShapesPerBodyLayerType.freeBuffer();
    mMatrices2.freeBuffer();
    mMatrices.freeBuffer();
    _e8.freeBuffer();
    mRigidBodies.freeBuffer();
}

void StaticCompoundRigidBodyGroup::init(const hkpPhysicsSystem& system, sead::Matrix34f* mtx,
                                        StaticCompound* sc, sead::Heap* heap) {
    mStaticCompound = sc;
    mMtxPtr = mtx;

    const int num_rigid_bodies = system.getRigidBodies().getSize();

    mRigidBodies.allocBuffer(num_rigid_bodies + NumBodyLayerTypes, heap);

    if (num_rigid_bodies > 0) {
        auto* group_handler = System::instance()->getStaticCompoundMgr()->getGroupHandler();

        mRigidBodiesPerBodyLayerType.allocBufferAssert(NumBodyLayerTypes, heap);
        mShapesPerBodyLayerType.allocBufferAssert(NumBodyLayerTypes, heap);
        for (int i = 0; i < NumBodyLayerTypes; ++i) {
            mRigidBodiesPerBodyLayerType[i] = nullptr;
            mShapesPerBodyLayerType[i] = nullptr;
        }

        for (int i = 0; i < num_rigid_bodies; ++i) {
            hkpRigidBody* hk_body = system.getRigidBodies()[i];

            bool is_entity = sead::SafeString(hk_body->getName()).include("Entity");
            auto layer_type = is_entity ? ContactLayerType::Entity : ContactLayerType::Sensor;

            auto* body = new (heap) RigidBodyFromResource(0.0, hk_body, layer_type, heap,
                                                          RigidBody::Type::StaticCompoundBody);

            RigidBodyInstanceParam param;
            param.max_linear_velocity = 1000;
            body->initMotionAccessor(param, heap, /* init_motion */ false);

            BodyLayerType body_layer_type = getBodyLayerType(body->getContactLayer());
            mRigidBodiesPerBodyLayerType[int(body_layer_type)] = body;

            body->updateCollidableQualityType(true);
            body->changeMotionType(MotionType::Fixed);
            if (body->isEntity()) {
                body->setSystemGroupHandler(group_handler);
                body->enableGroundCollision(false);
                body->enableWaterCollision(false);
            }

            mRigidBodies.pushBack(body);

            // XXX: eww, const_cast
            auto* shape = static_cast<hkpStaticCompoundShape*>(
                const_cast<hkpShape*>(system.getRigidBodies()[i]->getCollidable()->getShape()));
            shape->m_userData = reinterpret_cast<hkUlong>(this);
            mShapesPerBodyLayerType[int(body_layer_type)] = shape;
        }
    }

    mMatrices2.allocBufferAssert(BodyGroupNumMatrices, heap);
    mMatrices.allocBufferAssert(BodyGroupNumMatrices, heap);
    resetMatrices();

    mFlags.set(Flag::Initialised);
}

bool StaticCompoundRigidBodyGroup::isAnyRigidBodyAddedToWorld() const {
    for (int i = 0, n = mRigidBodies.size(); i < n; ++i) {
        if (mRigidBodies[i] && mRigidBodies[i]->isAddedToWorld())
            return true;
    }
    return false;
}

bool StaticCompoundRigidBodyGroup::isAnyRigidBodyBeingAddedToWorld() const {
    for (int i = 0, n = mRigidBodies.size(); i < n; ++i) {
        if (mRigidBodies[i] && mRigidBodies[i]->isAddingBodyToWorld())
            return true;
    }
    return false;
}

void StaticCompoundRigidBodyGroup::addToWorld() {
    for (int i = 0, n = mRigidBodies.size(); i < n; ++i) {
        auto* body = mRigidBodies[i];

        auto lock = body->makeScopedLock();

        body->setTransform(getTransform(), true);

        if (body->getMotionFlags().isOn(RigidBody::MotionFlag::BodyRemovalRequested)) {
            body->resetMotionFlagDirect(RigidBody::MotionFlag::BodyRemovalRequested);
        } else if (!body->isAddedToWorld() &&
                   !body->getMotionFlags().isOn(RigidBody::MotionFlag::BodyAddRequested)) {
            body->setMotionFlag(RigidBody::MotionFlag::BodyAddRequested);
        }
    }
}

void StaticCompoundRigidBodyGroup::removeFromWorld() {
    for (int i = 0, n = mRigidBodies.size(); i < n; ++i) {
        auto* body = mRigidBodies[i];

        auto lock = body->makeScopedLock();

        if (body->getMotionFlags().isOn(RigidBody::MotionFlag::BodyAddRequested)) {
            body->resetMotionFlagDirect(RigidBody::MotionFlag::BodyAddRequested);
        } else if (body->isAddedToWorld() &&
                   !body->getMotionFlags().isOn(RigidBody::MotionFlag::BodyRemovalRequested)) {
            body->setMotionFlag(RigidBody::MotionFlag::BodyRemovalRequested);
        }
    }
}

void StaticCompoundRigidBodyGroup::removeFromWorldImmediately() {
    for (int i = 0, n = mRigidBodies.size(); i < n; ++i)
        mRigidBodies[i]->removeFromWorldImmediately();
}

bool StaticCompoundRigidBodyGroup::setInstanceEnabled(BodyLayerType body_layer_type,
                                                      int instance_id, bool enabled) {
    hkpStaticCompoundShape* shape = mShapesPerBodyLayerType[int(body_layer_type)];
    shape->setInstanceEnabled(instance_id, enabled);
    mFlags.set(Flag::HasEnabledOrDisabledInstance);
    return true;
}

void StaticCompoundRigidBodyGroup::enableAllInstancesAndShapeKeys() {
    for (int i = 0, n = mShapesPerBodyLayerType.size(); i < n; ++i) {
        auto* shape = mShapesPerBodyLayerType[i];
        if (shape)
            shape->enableAllInstancesAndShapeKeys();
    }
}

void StaticCompoundRigidBodyGroup::resetMatrices() {
    for (int i = 0, n = mMatrices2.size(); i < n; ++i) {
        mMatrices2[i].makeIdentity();
        mMatrices[i].makeIdentity();
    }
}

void StaticCompoundRigidBodyGroup::resetMatricesAndUpdateTransform() {
    resetMatrices();
    mModifiedMatrices = 0;

    ScopedWorldLock lock_entity{ContactLayerType::Entity};
    ScopedWorldLock lock_sensor{ContactLayerType::Sensor};
    restoreMatricesAndUpdateTransform();
}

void StaticCompoundRigidBodyGroup::restoreMatricesAndUpdateTransform() {
    mFlags.set(Flag::_2);
    mFlags.set(Flag::_4);

    if (mModifiedMatrices != 0) {
        for (int i = 0, n = mMatrices.size(); i < n; ++i) {
            if ((1 << i) & mModifiedMatrices) {
                auto& dest = mMatrices2[i];
                dest = mMatrices[i];
            }
        }
        mModifiedMatrices = 0;
    }

    for (int i = 0, n = mRigidBodies.size(); i < n; ++i) {
        mRigidBodies[i]->setTransform(getTransform(), true);
    }
}

void StaticCompoundRigidBodyGroup::restoreMatrices() {
    if (mModifiedMatrices != 0) {
        for (int i = 0, n = mMatrices.size(); i < n; ++i) {
            if ((1 << i) & mModifiedMatrices) {
                auto& dest = mMatrices2[i];
                dest = mMatrices[i];
            }
        }
        mModifiedMatrices = 0;
        mFlags.set(Flag::_2);
        mFlags.set(Flag::_4);
    }
    mTransform = getTransform();
}

void StaticCompoundRigidBodyGroup::setMatrix(const sead::Matrix34f& matrix, int index) {
    if (mMatrices[index] == matrix)
        return;

    mMatrices[index] = matrix;
    mModifiedMatrices |= 1 << index;
    mFlags.set(Flag::ShouldMoveBody);
}

const sead::Matrix34f& StaticCompoundRigidBodyGroup::getMatrix(int index) const {
    return mMatrices[index];
}

sead::Matrix34f
StaticCompoundRigidBodyGroup::getTransformedMatrix(const sead::Matrix34f& mtx) const {
    return getTransform() * mtx;
}

sead::Matrix34f
StaticCompoundRigidBodyGroup::getInvTransformedMatrix(const sead::Matrix34f& mtx) const {
    sead::Matrix34f inv_transform;
    inv_transform.setInverse(getTransform());
    return inv_transform * mtx;
}

sead::Vector3f StaticCompoundRigidBodyGroup::getTransformedPos(const sead::Vector3f& pos) const {
    return getTransform() * pos;
}

sead::Vector3f StaticCompoundRigidBodyGroup::getRotatedDir(const sead::Vector3f& dir) const {
    sead::Vector3f rotated;
    rotated.setRotated(getTransform(), dir);
    return rotated;
}

void StaticCompoundRigidBodyGroup::processUpdates() {
    if (mFlags.isOn(Flag::HasEnabledOrDisabledInstance)) {
        for (int i = 0, n = mRigidBodies.size(); i < n; ++i) {
            mRigidBodies[i]->updateShape();
            mFlags.reset(Flag::HasEnabledOrDisabledInstance);
        }
    }

    if (mFlags.isOn(Flag::ShouldMoveBody) || mFlags.isOn(Flag::IsMovingBody)) {
        bool initialised_velocities = false;
        sead::Vector3f linvel, angvel;

        for (int i = 0, n = mRigidBodies.size(); i < n; ++i) {
            auto* body = mRigidBodies[i];

            body->changeMotionType(MotionType::Keyframed);

            if (!initialised_velocities) {
                body->computeVelocities(&linvel, &angvel, mTransform);

                if (mFlags.isOff(Flag::ShouldMoveBody)) {
                    linvel *= getVelocityMultiplier();
                    angvel *= getVelocityMultiplier();
                }

                util::lerp(&linvel, mLinearVelocity, linvel, getConfig().unk2);
                util::lerp(&angvel, mAngularVelocity, angvel, getConfig().unk3);
            }

            body->setLinearVelocity(linvel, getEpsilons().linvel);
            body->setAngularVelocity(angvel, getEpsilons().angvel);
            initialised_velocities = true;
        }

        mLinearVelocity = linvel;
        mAngularVelocity = angvel;

        if (mFlags.isOn(Flag::ShouldMoveBody)) {
            mUpdateTimer = getConfig().move_duration_ticks;
            mFlags.set(Flag::IsMovingBody);
        } else if (mUpdateTimer-- > 0) {
            mFlags.set(Flag::IsMovingBody);
        } else {
            mFlags.reset(Flag::IsMovingBody);
        }

        mFlags.reset(Flag::ShouldMoveBody);

    } else {
        for (int i = 0, n = mRigidBodies.size(); i < n; ++i) {
            auto* body = mRigidBodies[i];
            body->setLinearVelocity(sead::Vector3f::zero, getEpsilons().linvel);
            body->setAngularVelocity(sead::Vector3f::zero, getEpsilons().angvel);
            mLinearVelocity = {0, 0, 0};
            mAngularVelocity = {0, 0, 0};
        }
    }
}

float StaticCompoundRigidBodyGroup::getVelocityMultiplier() const {
    return getConfig().unk1 * float(mUpdateTimer) / float(getConfig().move_duration_ticks);
}

const sead::Matrix34f& StaticCompoundRigidBodyGroup::getTransform() const {
    if (!mFlags.isOn(Flag::Initialised))
        return sead::Matrix34f::ident;

    if (mFlags.isOn(Flag::_2)) {
        mMtx0 = mMatrices2[0];
        for (int i = 1, n = mMatrices2.size(); i < n; ++i)
            mMtx0 = mMatrices2[i] * mMtx0;

        mFlags.reset(Flag::_2);
    }

    if (mFlags.isOn(Flag::_4) && mMtxPtr) {
        mTransform = *mMtxPtr * mMtx0;
        mFlags.reset(Flag::_4);
    }

    return mTransform;
}

}  // namespace ksys::phys
