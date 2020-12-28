#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerGlide : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerGlide, PlayerAction)
public:
    explicit PlayerGlide(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mGlideSpeedMax_s{};
    // static_param at offset 0x28
    const float* mLv2GlideSpeedMax_s{};
    // static_param at offset 0x30
    const float* mGlideBodyFrontX_s{};
    // static_param at offset 0x38
    const float* mGlideBodyBackX_s{};
    // static_param at offset 0x40
    const float* mGlideBodySideZ_s{};
    // static_param at offset 0x48
    const float* mGlideRotMax_s{};
    // static_param at offset 0x50
    const float* mGlideRotMin_s{};
    // static_param at offset 0x58
    const float* mGlideRotRate_s{};
    // static_param at offset 0x60
    const float* mWindScale_s{};
    // static_param at offset 0x68
    const float* mOverSpeedDec_s{};
    // static_param at offset 0x70
    const float* mGlideRotSpeed_s{};
    // static_param at offset 0x78
    const float* mGlideNoSideAngle_s{};
};

}  // namespace uking::action
