#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerHide : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerHide, PlayerAction)
public:
    explicit PlayerHide(const InitArg& arg);
    ~PlayerHide() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x20
    const bool* mHidden_s{};
};

}  // namespace uking::action
