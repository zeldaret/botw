#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimeDrivenTurn : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnimeDrivenTurn, ksys::act::ai::Action)
public:
    explicit AnimeDrivenTurn(const InitArg& arg);
    ~AnimeDrivenTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAllowChangeableFrame_s{};
    // static_param at offset 0x28
    const float* mAnimPlayRate_s{};
    // static_param at offset 0x30
    const float* mFinishAngleRange_s{};
    // static_param at offset 0x38
    const float* mRotateAngleMax_s{};
    // static_param at offset 0x40
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0x48
    const bool* mIsAllowAnimeDrivenNoChangeAS_s{};
    // static_param at offset 0x50
    sead::SafeString mASKeyName_s{};
    // static_param at offset 0x60
    sead::SafeString mTargetBone_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
