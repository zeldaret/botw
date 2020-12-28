#pragma once

#include "Game/AI/Action/actionPlayerStoleOpenEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerStoleOpen : public PlayerStoleOpenEx {
    SEAD_RTTI_OVERRIDE(PlayerStoleOpen, PlayerStoleOpenEx)
public:
    explicit PlayerStoleOpen(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd8
    const float* mEnlargeSpd_s{};
};

}  // namespace uking::action
