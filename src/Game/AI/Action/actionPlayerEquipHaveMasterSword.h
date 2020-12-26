#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerEquipHaveMasterSword : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerEquipHaveMasterSword, PlayerAction)
public:
    explicit PlayerEquipHaveMasterSword(const InitArg& arg);
    ~PlayerEquipHaveMasterSword() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
