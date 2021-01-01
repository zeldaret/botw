#pragma once

#include "Game/AI/Action/actionPlayerGuidedMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerRailMove : public PlayerGuidedMove {
    SEAD_RTTI_OVERRIDE(PlayerRailMove, PlayerGuidedMove)
public:
    explicit PlayerRailMove(const InitArg& arg);
    ~PlayerRailMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x58
    sead::SafeString mRailName_d{};
};

}  // namespace uking::action
