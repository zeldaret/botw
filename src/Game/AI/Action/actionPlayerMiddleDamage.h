#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerMiddleDamage : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerMiddleDamage, PlayerAction)
public:
    explicit PlayerMiddleDamage(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mBaseInitSpeedNSword_s{};
    // static_param at offset 0x28
    const float* mBaseInitSpeedLSword_s{};
    // static_param at offset 0x30
    const float* mBaseInitSpeedSpear_s{};
    // static_param at offset 0x38
    const float* mBaseInitSpeedOther_s{};
    // static_param at offset 0x40
    const float* mAddSpeedNSword_s{};
    // static_param at offset 0x48
    const float* mAddSpeedLSword_s{};
    // static_param at offset 0x50
    const float* mAddSpeedSpear_s{};
    // static_param at offset 0x58
    const float* mAddSpeedOther_s{};
    // static_param at offset 0x60
    const float* mMaxSpeedNSword_s{};
    // static_param at offset 0x68
    const float* mMaxSpeedLSword_s{};
    // static_param at offset 0x70
    const float* mMaxSpeedSpear_s{};
    // static_param at offset 0x78
    const float* mMaxSpeedOther_s{};
    // static_param at offset 0x80
    const float* mDecSpeedNSword_s{};
    // static_param at offset 0x88
    const float* mDecSpeedLSword_s{};
    // static_param at offset 0x90
    const float* mDecSpeedSpear_s{};
    // static_param at offset 0x98
    const float* mDecSpeedOther_s{};
};

}  // namespace uking::action
