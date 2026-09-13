#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASHoldLinearMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASHoldLinearMove, ksys::act::ai::Action)
public:
    explicit ForkASHoldLinearMove(const InitArg& arg);
    ~ForkASHoldLinearMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMoveSpeed_s{};
    // static_param at offset 0x28
    const float* mRotRestRatio_s{};
    // static_param at offset 0x30
    const float* mPosRestRatio_s{};
    // static_param at offset 0x38
    const bool* mGravityTransReduce_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mMoveDir_s{};
};

}  // namespace uking::action
