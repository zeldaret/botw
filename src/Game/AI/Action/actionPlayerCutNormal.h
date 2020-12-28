#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerCutNormal : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerCutNormal, PlayerAction)
public:
    explicit PlayerCutNormal(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAttackRatioNSwordS1_s{};
    // static_param at offset 0x28
    const float* mAttackRatioNSwordS2_s{};
    // static_param at offset 0x30
    const float* mAttackRatioNSwordS3_s{};
    // static_param at offset 0x38
    const float* mAttackRatioLSwordS1_s{};
    // static_param at offset 0x40
    const float* mAttackRatioLSwordS2_s{};
    // static_param at offset 0x48
    const float* mAttackRatioLSwordS3_s{};
    // static_param at offset 0x50
    const float* mAttackRatioSpearS1_s{};
    // static_param at offset 0x58
    const float* mAttackRatioSpearS2_s{};
    // static_param at offset 0x60
    const float* mAttackRatioSpearS3_s{};
    // static_param at offset 0x68
    const float* mAttackRatioSpearS4_s{};
    // static_param at offset 0x70
    const float* mAttackRatioSpearS5_s{};
    // static_param at offset 0x78
    const float* mSwordSearchFrame_s{};
    // static_param at offset 0x80
    const float* mSwordSearchAngle_s{};
};

}  // namespace uking::action
