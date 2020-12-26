#pragma once

#include "Game/AI/Action/actionBattleCloseMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseMove : public BattleCloseMoveAction {
    SEAD_RTTI_OVERRIDE(BattleCloseMove, BattleCloseMoveAction)
public:
    explicit BattleCloseMove(const InitArg& arg);
    ~BattleCloseMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
