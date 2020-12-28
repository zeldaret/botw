#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerWaterFall : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerWaterFall, PlayerAction)
public:
    explicit PlayerWaterFall(const InitArg& arg);
    ~PlayerWaterFall() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeedClimb_s{};
    // dynamic_param at offset 0x28
    ksys::Rail** mRailPtr_d{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mFrontDir_d{};
};

}  // namespace uking::action
