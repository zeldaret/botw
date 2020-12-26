#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSetVisibleWeapon : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerSetVisibleWeapon, PlayerAction)
public:
    explicit PlayerSetVisibleWeapon(const InitArg& arg);
    ~PlayerSetVisibleWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mSetVisible_d{};
};

}  // namespace uking::action
