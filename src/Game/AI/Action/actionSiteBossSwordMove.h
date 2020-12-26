#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossSwordMove, ksys::act::ai::Action)
public:
    explicit SiteBossSwordMove(const InitArg& arg);
    ~SiteBossSwordMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAfterImage0AppearFrame_s{};
    // static_param at offset 0x28
    const float* mAfterImage1AppearFrame_s{};
    // static_param at offset 0x30
    const float* mAppearFrame_s{};
    // dynamic_param at offset 0x38
    float* mCurrentFrame_d{};
    // dynamic_param at offset 0x40
    bool* mIsCloseMove_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mMoveDstPos_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mAfterImage0Pos_d{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mAfterImage1Pos_d{};
};

}  // namespace uking::action
