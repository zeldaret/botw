#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerBeetleSubject : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerBeetleSubject, PlayerAction)
public:
    explicit PlayerBeetleSubject(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAimRange_s{};
};

}  // namespace uking::action
