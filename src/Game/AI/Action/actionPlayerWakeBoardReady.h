#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerWakeBoardReady : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerWakeBoardReady, PlayerAction)
public:
    explicit PlayerWakeBoardReady(const InitArg& arg);
    ~PlayerWakeBoardReady() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mCreateSelf_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mUniqueName_d{};
};

}  // namespace uking::action
