#pragma once

#include "Game/AI/Action/actionPriestBossWarpOrVanish.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossFastWarpMove : public PriestBossWarpOrVanish {
    SEAD_RTTI_OVERRIDE(PriestBossFastWarpMove, PriestBossWarpOrVanish)
public:
    explicit PriestBossFastWarpMove(const InitArg& arg);
    ~PriestBossFastWarpMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x28
    const float* mAfterImage0AppearFrame_s{};
    // static_param at offset 0x30
    const float* mAfterImage1AppearFrame_s{};
    // static_param at offset 0x38
    const float* mAppearFrame_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x50
    float* mCurrentFrame_d{};
    // dynamic_param at offset 0x58
    bool* mIsCloseMove_d{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mMoveDstPos_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mAfterImage0Pos_d{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mAfterImage1Pos_d{};
};

}  // namespace uking::action
