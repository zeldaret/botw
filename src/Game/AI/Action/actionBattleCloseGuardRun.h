#pragma once

#include "Game/AI/Action/actionBattleCloseMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseGuardRun : public BattleCloseMoveAction {
    SEAD_RTTI_OVERRIDE(BattleCloseGuardRun, BattleCloseMoveAction)
public:
    explicit BattleCloseGuardRun(const InitArg& arg);
    ~BattleCloseGuardRun() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
