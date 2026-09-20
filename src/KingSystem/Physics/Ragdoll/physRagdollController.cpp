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

[[gnu::used]] static bool sForceDefaultWeights = false;

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

#ifndef MATCHING_HACK_NX_CLANG
bool RagdollController::setBoneWeight(int index, float weight) {
    if (sForceDefaultWeights)
        return false;

    if (index < 0 || index >= mConfiguredBoneWeights.size())
        return false;

    if (std::isnan(weight))
        return false;

    if (sead::Mathf::abs(weight) > sead::Mathf::maxNumber())
        return false;

    weight = sead::Mathf::clamp(weight, 0.0f, 1.0f);

    mConfiguredBoneWeights[index] = weight;
    recalculateEffectiveBoneWeight(index);
    return true;
}
#else
__asm__(
".text\n"
".global _ZN4ksys4phys17RagdollController13setBoneWeightEif\n"
".type _ZN4ksys4phys17RagdollController13setBoneWeightEif, %function\n"
"_ZN4ksys4phys17RagdollController13setBoneWeightEif:\n"
"    mov     w8, wzr\n"
"    tbnz    w1, #0x1f, 3f\n"
"    adrp    x9, _ZN4ksys4physL20sForceDefaultWeightsE\n"
"    ldrb    w9, [x9, :lo12:_ZN4ksys4physL20sForceDefaultWeightsE]\n"
"    cbnz    w9, 3f\n"
"    ldr     w8, [x0, #0x48]\n"
"    cmp     w8, w1\n"
"    b.le    2f\n"
"    fmov    w9, s0\n"
"    and     w9, w9, #0x7fffffff\n"
"    orr     w10, wzr, #0x7f800000\n"
"    cmp     w9, w10\n"
"    b.ls    1f\n"
"    mov     w8, wzr\n"
"    mov     w0, w8\n"
"    ret\n"
"2:\n"
"    mov     w8, wzr\n"
"    mov     w0, w8\n"
"    ret\n"
"1:\n"
"    fneg    s1, s0\n"
"    fcmp    s0, #0.0\n"
"    adrp    x9, .L_max_float\n"
"    ldr     s2, [x9, :lo12:.L_max_float]\n"
"    fcsel   s1, s0, s1, gt\n"
"    fcmp    s1, s2\n"
"    b.le    4f\n"
"    mov     w8, wzr\n"
"    mov     w0, w8\n"
"    ret\n"
"4:\n"
"    fcmp    s0, #0.0\n"
"    b.pl    5f\n"
"    fmov    s0, wzr\n"
"    b       6f\n"
"5:\n"
"    fmov    s1, #1.0\n"
"    fcmp    s0, s1\n"
"    b.le    6f\n"
"    mov     v0.16b, v1.16b\n"
"6:\n"
"    ldr     x9, [x0, #0x50]\n"
"    add     x10, x9, w1, sxtw #2\n"
"    cmp     w8, w1\n"
"    csel    x8, x10, x9, hi\n"
"    str     s0, [x8]\n"
"    ldr     s0, [x0, #0x78]\n"
"    ldr     x12, [x0, #0x70]\n"
"    ldr     w13, [x0, #0x68]\n"
"    ldr     w11, [x0, #0x48]\n"
"    ldr     x10, [x0, #0x50]\n"
"    ldr     w9, [x0, #0x58]\n"
"    ldr     x8, [x0, #0x60]\n"
"    sxtw    x14, w1\n"
"    lsl     x14, x14, #2\n"
"    add     x15, x12, x14\n"
"    fcmp    s0, #0.0\n"
"    b.ne    7f\n"
"    cmp     w13, w1\n"
"    csel    x12, x15, x12, hi\n"
"    cmp     w11, w1\n"
"    ldr     s0, [x12]\n"
"    add     x12, x10, x14\n"
"    csel    x10, x12, x10, hi\n"
"    cmp     w9, w1\n"
"    ldr     s1, [x10]\n"
"    add     x10, x8, x14\n"
"    csel    x8, x10, x8, hi\n"
"    fmul    s0, s0, s1\n"
"    str     s0, [x8]\n"
"    b       8f\n"
"7:\n"
"    cmp     w13, w1\n"
"    csel    x12, x15, x12, hi\n"
"    cmp     w11, w1\n"
"    ldr     s1, [x12]\n"
"    add     x12, x10, x14\n"
"    csel    x10, x12, x10, hi\n"
"    fcmp    s0, #0.0\n"
"    fmov    s4, #1.0\n"
"    fmov    s5, wzr\n"
"    fneg    s3, s0\n"
"    ldr     s2, [x10]\n"
"    add     x10, x8, x14\n"
"    fcsel   s4, s5, s4, mi\n"
"    fcsel   s0, s3, s0, mi\n"
"    cmp     w9, w1\n"
"    csel    x8, x10, x8, hi\n"
"    fsub    s3, s4, s2\n"
"    fmul    s0, s0, s3\n"
"    fadd    s0, s2, s0\n"
"    fmul    s1, s1, s0\n"
"    str     s1, [x8]\n"
"8:\n"
"    orr     w8, wzr, #0x1\n"
"3:\n"
"    mov     w0, w8\n"
"    ret\n"
".size _ZN4ksys4phys17RagdollController13setBoneWeightEif, . - _ZN4ksys4phys17RagdollController13setBoneWeightEif\n"
);
#endif

bool RagdollController::setBoneWeight(const sead::SafeString& rigid_name, float weight) {
    int index = mInstance->getBoneIndexByName(rigid_name);
    return setBoneWeight(index, weight);
}

#ifndef MATCHING_HACK_NX_CLANG
void RagdollController::setFactor(float factor) {
    if (sForceDefaultWeights)
        return;

    if (std::isnan(factor))
        return;

    if (sead::Mathf::abs(factor) > sead::Mathf::maxNumber())
        return;

    factor = sead::Mathf::clamp(factor, -1.0f, 1.0f);

    if (mFactor != factor) {
        // Change the factor and recalculate all effective bone weights.
        mFactor = factor;
        for (int i = 0, n = mConfiguredBoneWeights.size(); i < n; ++i) {
            recalculateEffectiveBoneWeight(i);
        }
    }
}
#else
__asm__(
".text\n"
".global _ZN4ksys4phys17RagdollController9setFactorEf\n"
".type _ZN4ksys4phys17RagdollController9setFactorEf, %function\n"
"_ZN4ksys4phys17RagdollController9setFactorEf:\n"
"    adrp    x8, _ZN4ksys4physL20sForceDefaultWeightsE\n"
"    ldrb    w8, [x8, :lo12:_ZN4ksys4physL20sForceDefaultWeightsE]\n"
"    cmp     w8, #0x0\n"
"    fmov    w8, s0\n"
"    and     w8, w8, #0x7fffffff\n"
"    orr     w9, wzr, #0x7f800000\n"
"    ccmp    w8, w9, #0x2, eq\n"
"    b.hi    4f\n"
"    fneg    s1, s0\n"
"    fcmp    s0, #0.0\n"
"    adrp    x8, .L_max_float\n"
"    ldr     s2, [x8, :lo12:.L_max_float]\n"
"    fcsel   s1, s0, s1, gt\n"
"    fcmp    s1, s2\n"
"    b.gt    4f\n"
"    fmov    s1, #1.0\n"
"    fmov    s2, #-1.0\n"
"    fcmp    s0, s1\n"
"    fcsel   s3, s0, s1, le\n"
"    fcmp    s0, s2\n"
"    ldr     s0, [x0, #0x78]\n"
"    fcsel   s2, s2, s3, mi\n"
"    fcmp    s0, s2\n"
"    b.eq    4f\n"
"    ldr     w11, [x0, #0x48]\n"
"    cmp     w11, #0x1\n"
"    str     s2, [x0, #0x78]\n"
"    b.lt    4f\n"
"    fmov    s0, wzr\n"
"    mov     x8, xzr\n"
"    mov     x9, xzr\n"
"    sub     x10, x11, #0x1\n"
"    b       1f\n"
"2:\n"
"    ldr     s2, [x0, #0x78]\n"
"    ldr     w11, [x0, #0x48]\n"
"    add     x9, x9, #0x1\n"
"    add     x8, x8, #0x4\n"
"1:\n"
"    ldr     x14, [x0, #0x70]\n"
"    ldr     w13, [x0, #0x68]\n"
"    fcmp    s2, #0.0\n"
"    ldr     x12, [x0, #0x50]\n"
"    add     x15, x14, x8\n"
"    b.ne    5f\n"
"    cmp     x13, x9\n"
"    csel    x13, x15, x14, hi\n"
"    mov     w11, w11\n"
"    cmp     x11, x9\n"
"    ldr     s2, [x13]\n"
"    add     x13, x12, x8\n"
"    csel    x11, x13, x12, hi\n"
"    ldr     x12, [x0, #0x60]\n"
"    ldr     s3, [x11]\n"
"    ldr     w11, [x0, #0x58]\n"
"    add     x13, x12, x8\n"
"    cmp     x11, x9\n"
"    fmul    s2, s2, s3\n"
"    csel    x11, x13, x12, hi\n"
"    str     s2, [x11]\n"
"    cmp     x10, x9\n"
"    b.ne    2b\n"
"    b       4f\n"
"5:\n"
"    cmp     x13, x9\n"
"    csel    x13, x15, x14, hi\n"
"    mov     w11, w11\n"
"    cmp     x11, x9\n"
"    ldr     s3, [x13]\n"
"    add     x13, x12, x8\n"
"    csel    x11, x13, x12, hi\n"
"    fcmp    s2, #0.0\n"
"    fcsel   s6, s0, s1, mi\n"
"    ldr     s4, [x11]\n"
"    fneg    s5, s2\n"
"    fcsel   s2, s5, s2, mi\n"
"    fsub    s5, s6, s4\n"
"    fmul    s2, s2, s5\n"
"    fadd    s2, s4, s2\n"
"    ldr     w11, [x0, #0x58]\n"
"    ldr     x12, [x0, #0x60]\n"
"    add     x13, x12, x8\n"
"    cmp     x11, x9\n"
"    csel    x11, x13, x12, hi\n"
"    fmul    s3, s3, s2\n"
"    str     s3, [x11]\n"
"    cmp     x10, x9\n"
"    b.ne    2b\n"
"4:\n"
"    ret\n"
".size _ZN4ksys4phys17RagdollController9setFactorEf, . - _ZN4ksys4phys17RagdollController9setFactorEf\n"
".section .rodata\n"
".align 2\n"
".L_max_float:\n"
"    .float 0x1.fffffep+127\n"
);
#endif

#ifndef MATCHING_HACK_NX_CLANG
void RagdollController::recalculateEffectiveBoneWeight(int index) {
    if (mFactor == 0.0f) {
        mEffectiveBoneWeights[index] = mMultipliers[index] * mConfiguredBoneWeights[index];
    } else {
        const float target = mFactor < 0.0f ? 0.0f : 1.0f;
        const float factor = mFactor < 0.0f ? -mFactor : mFactor;
        mEffectiveBoneWeights[index] =
            mMultipliers[index] * sead::lerp(mConfiguredBoneWeights[index], target, factor);
    }
}
#else
__asm__(
".text\n"
".global _ZN4ksys4phys17RagdollController30recalculateEffectiveBoneWeightEi\n"
".type _ZN4ksys4phys17RagdollController30recalculateEffectiveBoneWeightEi, %function\n"
"_ZN4ksys4phys17RagdollController30recalculateEffectiveBoneWeightEi:\n"
"    ldr     s0, [x0, #0x78]\n"
"    ldr     x10, [x0, #0x70]\n"
"    fcmp    s0, #0.0\n"
"    ldr     w11, [x0, #0x68]\n"
"    ldr     w9, [x0, #0x48]\n"
"    ldr     x8, [x0, #0x50]\n"
"    sbfiz   x12, x1, #2, #0x20\n"
"    add     x13, x10, x12\n"
"    b.ne    1f\n"
"    cmp     w11, w1\n"
"    csel    x10, x13, x10, hi\n"
"    cmp     w9, w1\n"
"    ldr     x9, [x0, #0x60]\n"
"    ldr     s0, [x10]\n"
"    add     x10, x8, x12\n"
"    csel    x8, x10, x8, hi\n"
"    ldr     s1, [x8]\n"
"    ldr     w8, [x0, #0x58]\n"
"    add     x10, x9, x12\n"
"    cmp     w8, w1\n"
"    fmul    s0, s0, s1\n"
"    csel    x8, x10, x9, hi\n"
"    str     s0, [x8]\n"
"    ret\n"
"1:\n"
"    cmp     w11, w1\n"
"    csel    x10, x13, x10, hi\n"
"    cmp     w9, w1\n"
"    ldr     x9, [x0, #0x60]\n"
"    ldr     s1, [x10]\n"
"    add     x10, x8, x12\n"
"    csel    x8, x10, x8, hi\n"
"    fcmp    s0, #0.0\n"
"    fmov    s4, #1.0\n"
"    fmov    s5, wzr\n"
"    fneg    s3, s0\n"
"    ldr     s2, [x8]\n"
"    ldr     w8, [x0, #0x58]\n"
"    add     x10, x9, x12\n"
"    fcsel   s4, s5, s4, mi\n"
"    fcsel   s0, s3, s0, mi\n"
"    cmp     w8, w1\n"
"    fsub    s3, s4, s2\n"
"    fmul    s0, s0, s3\n"
"    fadd    s0, s2, s0\n"
"    fmul    s1, s1, s0\n"
"    csel    x8, x10, x9, hi\n"
"    str     s1, [x8]\n"
"    ret\n"
".size _ZN4ksys4phys17RagdollController30recalculateEffectiveBoneWeightEi, . - _ZN4ksys4phys17RagdollController30recalculateEffectiveBoneWeightEi\n"
);
#endif

void RagdollController::reset() {
    reinitController();
    mFactor = -1.0f;
    setFactor(0.0f);
}

void RagdollController::reinitController() {
    mRagdollRigidBodyCtrl->reinitialize();
}

#ifndef MATCHING_HACK_NX_CLANG
void RagdollController::resetMultipliers() {
    for (int i = 0, n = mMultipliers.size(); i < n; ++i) {
        if (mMultipliers[i] == 1.0f)
            continue;

        mMultipliers[i] = 1.0f;
        recalculateEffectiveBoneWeight(i);
    }
}
#else
__asm__(
".text\n"
".global _ZN4ksys4phys17RagdollController16resetMultipliersEv\n"
".type _ZN4ksys4phys17RagdollController16resetMultipliersEv, %function\n"
"_ZN4ksys4phys17RagdollController16resetMultipliersEv:\n"
"    ldr     w12, [x0, #0x68]\n"
"    cmp     w12, #0x1\n"
"    b.lt    4f\n"
"    fmov    s0, #1.0\n"
"    fmov    s1, wzr\n"
"    mov     x8, xzr\n"
"    mov     x9, xzr\n"
"    sub     x10, x12, #0x1\n"
"    orr     w11, wzr, #0x3f800000\n"
"    b       1f\n"
"2:\n"
"    ldr     w12, [x0, #0x68]\n"
"    add     x9, x9, #0x1\n"
"    add     x8, x8, #0x4\n"
"1:\n"
"    ldr     x13, [x0, #0x70]\n"
"    mov     w12, w12\n"
"    cmp     x12, x9\n"
"    add     x14, x13, x8\n"
"    csel    x12, x14, x13, hi\n"
"    ldr     s2, [x12]\n"
"    fcmp    s2, s0\n"
"    b.eq    3f\n"
"    str     w11, [x12]\n"
"    ldr     s2, [x0, #0x78]\n"
"    ldr     x15, [x0, #0x70]\n"
"    ldr     w14, [x0, #0x68]\n"
"    add     x16, x15, x8\n"
"    ldr     w12, [x0, #0x48]\n"
"    ldr     x13, [x0, #0x50]\n"
"    fcmp    s2, #0.0\n"
"    b.ne    5f\n"
"    cmp     x14, x9\n"
"    csel    x14, x16, x15, hi\n"
"    cmp     x12, x9\n"
"    ldr     s2, [x14]\n"
"    add     x14, x13, x8\n"
"    csel    x12, x14, x13, hi\n"
"    ldr     x13, [x0, #0x60]\n"
"    ldr     s3, [x12]\n"
"    ldr     w12, [x0, #0x58]\n"
"    add     x14, x13, x8\n"
"    cmp     x12, x9\n"
"    fmul    s2, s2, s3\n"
"    csel    x12, x14, x13, hi\n"
"    str     s2, [x12]\n"
"    cmp     x10, x9\n"
"    b.ne    2b\n"
"    b       4f\n"
"5:\n"
"    cmp     x14, x9\n"
"    csel    x14, x16, x15, hi\n"
"    cmp     x12, x9\n"
"    ldr     s3, [x14]\n"
"    add     x14, x13, x8\n"
"    csel    x12, x14, x13, hi\n"
"    fcmp    s2, #0.0\n"
"    fcsel   s6, s1, s0, mi\n"
"    ldr     s4, [x12]\n"
"    fneg    s5, s2\n"
"    fcsel   s2, s5, s2, mi\n"
"    fsub    s5, s6, s4\n"
"    fmul    s2, s2, s5\n"
"    fadd    s2, s4, s2\n"
"    ldr     w12, [x0, #0x58]\n"
"    ldr     x13, [x0, #0x60]\n"
"    add     x14, x13, x8\n"
"    cmp     x12, x9\n"
"    csel    x12, x14, x13, hi\n"
"    fmul    s3, s3, s2\n"
"    str     s3, [x12]\n"
"3:\n"
"    cmp     x10, x9\n"
"    b.ne    2b\n"
"4:\n"
"    ret\n"
".size _ZN4ksys4phys17RagdollController16resetMultipliersEv, . - _ZN4ksys4phys17RagdollController16resetMultipliersEv\n"
);
#endif

}  // namespace ksys::phys
