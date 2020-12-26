#pragma once

#include "Game/AI/Action/actionGiantBattleCloseAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantBattleCloseMove : public GiantBattleCloseAction {
    SEAD_RTTI_OVERRIDE(GiantBattleCloseMove, GiantBattleCloseAction)
public:
    explicit GiantBattleCloseMove(const InitArg& arg);
    ~GiantBattleCloseMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
