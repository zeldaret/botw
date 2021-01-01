#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerTalk : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerTalk, PlayerAction)
public:
    explicit PlayerTalk(const InitArg& arg);
    ~PlayerTalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xc0
    sead::SafeString mGreetingType_d{};
};

}  // namespace uking::action
