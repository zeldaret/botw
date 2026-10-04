#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DefTurnAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DefTurnAction, ksys::act::ai::Action)
public:
    explicit DefTurnAction(const InitArg& arg);
    ~DefTurnAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWaitRotate_s{};
    // static_param at offset 0x28
    const float* mRotateSpeed_s{};
    // static_param at offset 0x30
    const float* mJumpHeight_s{};
    // static_param at offset 0x38
    sead::SafeString mASKeyName_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
