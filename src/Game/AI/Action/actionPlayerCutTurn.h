#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerCutTurn : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerCutTurn, PlayerAction)
public:
    explicit PlayerCutTurn(const InitArg& arg);
    ~PlayerCutTurn() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mMaxChargeLvNSword_s{};
    // static_param at offset 0x28
    const float* mAttackRatioNSword_s{};
    // static_param at offset 0x30
    const float* mAttackRatioLSword_s{};
    // static_param at offset 0x38
    const float* mAttackRatioSpear_s{};
    // static_param at offset 0x40
    const float* mEnergyAttack_s{};
    // static_param at offset 0x48
    const float* mEnergyChargeStart_s{};
    // static_param at offset 0x50
    const float* mRangeDiam_s{};
    // static_param at offset 0x58
    const float* mRangeDiamAdd_s{};
    // static_param at offset 0x60
    const float* mRangeDiamAddNSword_s{};
};

}  // namespace uking::action
