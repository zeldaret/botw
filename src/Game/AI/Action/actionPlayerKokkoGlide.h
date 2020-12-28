#pragma once

#include "Game/AI/Action/actionPlayerGlide.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerKokkoGlide : public PlayerGlide {
    SEAD_RTTI_OVERRIDE(PlayerKokkoGlide, PlayerGlide)
public:
    explicit PlayerKokkoGlide(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    const float* mEnergyGlide_s{};
    // static_param at offset 0x90
    const float* mNoEnergyTime_s{};
};

}  // namespace uking::action
