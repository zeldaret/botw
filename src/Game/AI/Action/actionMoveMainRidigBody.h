#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveMainRidigBody : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MoveMainRidigBody, ksys::act::ai::Action)
public:
    explicit MoveMainRidigBody(const InitArg& arg);
    ~MoveMainRidigBody() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mFinLength_s{};
    // static_param at offset 0x28
    const float* mMaxSpeed_s{};
    // static_param at offset 0x30
    const float* mVibrateStopCheck_s{};
    // static_param at offset 0x38
    const float* mVibrateCheckFrame_s{};
    // static_param at offset 0x40
    const float* mVibrateMemoryStep_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mTargetPosOffset_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    // aitree_variable at offset 0x58
    void* mRefPosVibrateChecker_a{};
};

}  // namespace uking::action
