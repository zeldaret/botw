#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StalPartCatch : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StalPartCatch, ksys::act::ai::Action)
public:
    explicit StalPartCatch(const InitArg& arg);
    ~StalPartCatch() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mPartIndex_s{};
    // static_param at offset 0x28
    const float* mInputWeightTimer_s{};
    // static_param at offset 0x30
    const float* mBlendWeightTimer_s{};
    // static_param at offset 0x38
    sead::SafeString mBaseRagdollRigidBodyName_s{};
    // static_param at offset 0x48
    sead::SafeString mSecondRagdollRigidBodyName_s{};
    // static_param at offset 0x58
    sead::SafeString mThirdRagdollRigidBodyName_s{};
    // static_param at offset 0x68
    sead::SafeString mConstraintNames_s{};
    // static_param at offset 0x78
    sead::SafeString mFreeMoveRagdollRigidBodyNames_s{};
    // static_param at offset 0x88
    sead::SafeString mASName_s{};
    // static_param at offset 0x98
    sead::SafeString mUseRagConName_s{};
    // static_param at offset 0xa8
    const sead::Vector3f* mUnitePosOffset_s{};
    // static_param at offset 0xb0
    const sead::Vector3f* mUniteRotOffset_s{};
    // static_param at offset 0xb8
    const sead::Vector3f* mSecondUnitePosOffset_s{};
    // static_param at offset 0xc0
    const sead::Vector3f* mSecondUniteRotOffset_s{};
    // static_param at offset 0xc8
    const sead::Vector3f* mThirdUnitePosOffset_s{};
    // static_param at offset 0xd0
    const sead::Vector3f* mThirdUniteRotOffset_s{};
};

}  // namespace uking::action
