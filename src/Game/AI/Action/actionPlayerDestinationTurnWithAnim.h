#pragma once

#include "Game/AI/Action/actionPlayerDestinationTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerDestinationTurnWithAnim : public PlayerDestinationTurn {
    SEAD_RTTI_OVERRIDE(PlayerDestinationTurnWithAnim, PlayerDestinationTurn)
public:
    explicit PlayerDestinationTurnWithAnim(const InitArg& arg);
    ~PlayerDestinationTurnWithAnim() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x40
    bool* mIsWaitASFinish_d{};
    // dynamic_param at offset 0x48
    bool* mUsePartBind_d{};
    // dynamic_param at offset 0x50
    sead::SafeString mASName_d{};
};

}  // namespace uking::action
