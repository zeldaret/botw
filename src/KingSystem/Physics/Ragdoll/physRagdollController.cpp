#include "KingSystem/Physics/Ragdoll/physRagdollController.h"
#include <Havok/Animation/Physics2012Bridge/Controller/RigidBody/hkaRagdollRigidBodyController.h>
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/Ragdoll/physRagdollControllerKeyList.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

static bool sForceDefaultWeights = false;

void RagdollController::forceDefaultWeights(bool force) {
    sForceDefaultWeights = force;
}

RagdollController::RagdollController() = default;

RagdollController::~RagdollController() {
    if (mRagdollRigidBodyCtrl)
        util::safeDelete(mRagdollRigidBodyCtrl);
    mConfiguredBoneWeights.freeBuffer();
    mEffectiveBoneWeights.freeBuffer();
    mMultipliers.freeBuffer();
}

bool RagdollController::init(const sead::SafeString& name, const sead::SafeString& system_key,
                             RagdollInstance* instance, sead::Heap* heap) {
    mName = name;
    mInstance = instance;
    util::PrintDebugFmt("creating RagdollController for %s", mName.cstr());
    mRagdollRigidBodyCtrl = new hkaRagdollRigidBodyController(instance->getHavokRagdollInstance());

    const int num_bones = instance->getRigidBodies_().size();

    mConfiguredBoneWeights.allocBufferAssert(num_bones, heap);
    mEffectiveBoneWeights.allocBufferAssert(num_bones, heap);
    mMultipliers.allocBufferAssert(num_bones, heap);

    for (int i = 0; i < num_bones; ++i) {
        mConfiguredBoneWeights[i] = 1.0f;
        mEffectiveBoneWeights[i] = 1.0f;
        mMultipliers[i] = 1.0f;
    }

    // Configure the controller.
    mRagdollRigidBodyCtrl->setBoneWeights(mEffectiveBoneWeights.getBufferPtr());
    if (System::instance()->getRagdollCtrlKeyList() != nullptr) {
        auto* config =
            System::instance()->getRagdollCtrlKeyList()->getControllerKeyByKey(system_key);
        if (config != nullptr) {
            const auto get_control_data = [this]() -> decltype(auto) {
                return mRagdollRigidBodyCtrl->m_controlDataPalette[0];
            };

            get_control_data().m_hierarchyGain = *config->hierarchy_gain;
            get_control_data().m_velocityDamping = *config->velocity_damping;
            get_control_data().m_accelerationGain = *config->acceleration_gain;
            get_control_data().m_velocityGain = *config->velocity_gain;
            get_control_data().m_positionGain = *config->position_gain;
            get_control_data().m_positionMaxLinearVelocity = *config->position_max_linear_velocity;
            get_control_data().m_positionMaxAngularVelocity =
                *config->position_max_angular_velocity;
            get_control_data().m_snapGain = *config->snap_gain;
            get_control_data().m_snapMaxLinearVelocity = *config->snap_max_linear_velocity;
            get_control_data().m_snapMaxAngularVelocity = *config->snap_max_angular_velocity;
            get_control_data().m_snapMaxLinearDistance = *config->snap_max_linear_distance;
            get_control_data().m_snapMaxAngularDistance = *config->snap_max_angular_distance;
        }
    }

    return true;
}

bool RagdollController::setBoneWeight(int index, float weight) {
    if (sForceDefaultWeights)
        return false;

    if (index < 0 || index >= mConfiguredBoneWeights.size())
        return false;

    if (std::isnan(weight))
        return false;

    weight = sead::Mathf::abs(weight);

    if (weight > sead::Mathf::maxNumber())
        return false;

    weight = sead::Mathf::clamp(weight, 0.0, 1.0);

    mConfiguredBoneWeights[index] = weight;
    recalculateEffectiveBoneWeight(index);
    return true;
}

bool RagdollController::setBoneWeight(const sead::SafeString& rigid_name, float weight) {
    int index = mInstance->getBoneIndexByName(rigid_name);
    return setBoneWeight(index, weight);
}

void RagdollController::setFactor(float factor) {
    if (sForceDefaultWeights)
        return;

    if (std::isnan(factor))
        return;

    if (sead::Mathf::abs(factor) > sead::Mathf::maxNumber())
        return;

    factor = sead::Mathf::clamp(factor, -1.0, 1.0);

    if (mFactor != factor) {
        // Change the factor and recalculate all effective bone weights.
        mFactor = factor;
        for (int i = 0, n = mConfiguredBoneWeights.size(); i < n; ++i) {
            recalculateEffectiveBoneWeight(i);
        }
    }
}

// NON_MATCHING
void RagdollController::recalculateEffectiveBoneWeight(int index) {
    const auto factor = [this] { return mFactor < 0 ? -mFactor : mFactor; };

    if (mFactor == 0.0) {
        mEffectiveBoneWeights[index] = mMultipliers[index] * mConfiguredBoneWeights[index];
    } else if (mFactor < 0.0) {
        mEffectiveBoneWeights[index] =
            mMultipliers[index] *
            (mConfiguredBoneWeights[index] + (0.0f - mConfiguredBoneWeights[index]) * factor());
    } else {
        mEffectiveBoneWeights[index] =
            mMultipliers[index] *
            (mConfiguredBoneWeights[index] + (1.0f - mConfiguredBoneWeights[index]) * factor());
    }
}

void RagdollController::reset() {
    reinitController();
    mFactor = -1.0f;
    setFactor(0.0f);
}

void RagdollController::reinitController() {
    mRagdollRigidBodyCtrl->reinitialize();
}

void RagdollController::resetMultipliers() {
    for (int i = 0, n = mMultipliers.size(); i < n; ++i) {
        if (mMultipliers[i] == 1.0)
            continue;

        mMultipliers[i] = 1.0;
        recalculateEffectiveBoneWeight(i);
    }
}

}  // namespace ksys::phys
