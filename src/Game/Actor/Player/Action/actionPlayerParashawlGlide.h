#pragma once

#include "Game/Actor/Player/Action/actionPlayerParashawlGlideBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerParashawlGlide : public PlayerParashawlGlideBase {
    SEAD_RTTI_OVERRIDE(PlayerParashawlGlide, PlayerParashawlGlideBase)
public:
    explicit PlayerParashawlGlide(const InitArg& arg);

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
