#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GolemDieFromRagdoll : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GolemDieFromRagdoll, ksys::act::ai::Action)
public:
    explicit GolemDieFromRagdoll(const InitArg& arg);
    ~GolemDieFromRagdoll() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const float* mRagdollMoveLimitDist_s{};
    // static_param at offset 0x30
    const float* mBlownHeight_s{};
    // static_param at offset 0x38
    const float* mBlownSpeed_s{};
    // static_param at offset 0x40
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x48
    const float* mRotReduceRatio_s{};
    // static_param at offset 0xd0
    sead::SafeString mPosBaseRagdollRbName_s{};
    // static_param at offset 0xe0
    sead::SafeString mRagdollControllerKey_s{};
    // static_param at offset 0xf0
    sead::SafeString mXLinkKey_s{};
    // static_param at offset 0x100
    sead::SafeString mImpulseXLinkKey_s{};
};

}  // namespace uking::action
