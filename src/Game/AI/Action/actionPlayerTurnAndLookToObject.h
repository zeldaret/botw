#pragma once

#include "Game/AI/Action/actionPlayerLookAtObject.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerTurnAndLookToObject : public PlayerLookAtObject {
    SEAD_RTTI_OVERRIDE(PlayerTurnAndLookToObject, PlayerLookAtObject)
public:
    explicit PlayerTurnAndLookToObject(const InitArg& arg);
    ~PlayerTurnAndLookToObject() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xc8
    bool* mIsUseSlowTurn_d{};
    // dynamic_param at offset 0xd0
    bool* mIsTurnToLookAtPos_d{};
};

}  // namespace uking::action
