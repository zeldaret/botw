#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkTurn : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkTurn, ksys::act::ai::Action)
public:
    explicit ForkTurn(const InitArg& arg);
    ~ForkTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpd_s{};
    // static_param at offset 0x28
    const float* mFinRotate_s{};
    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    const float* mBaseRotRatio_s{};
    // static_param at offset 0x40
    const float* mRotAccRatio_s{};
    // static_param at offset 0x48
    const float* mRotAccMaxSpeedRatio_s{};
    // static_param at offset 0x50
    const bool* mIsUpdateTarget_s{};
    // static_param at offset 0x58
    const bool* mIsFollowGround_s{};
    // static_param at offset 0x60
    const bool* mIsRotEndFinish_s{};
    // static_param at offset 0x68
    const bool* mIsFinishForceStopRot_s{};
    // static_param at offset 0x70
    const bool* mIsChangeable_s{};
    // static_param at offset 0x78
    const bool* mIsUpFollow_s{};
};

}  // namespace uking::action
