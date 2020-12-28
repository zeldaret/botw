#pragma once

#include "Game/AI/Action/actionBattleCloseMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseGuardWalk : public BattleCloseMoveAction {
    SEAD_RTTI_OVERRIDE(BattleCloseGuardWalk, BattleCloseMoveAction)
public:
    explicit BattleCloseGuardWalk(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
