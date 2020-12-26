#pragma once

#include "Game/AI/Action/actionBattleCloseMoveActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseMoveAction : public BattleCloseMoveActionBase {
    SEAD_RTTI_OVERRIDE(BattleCloseMoveAction, BattleCloseMoveActionBase)
public:
    explicit BattleCloseMoveAction(const InitArg& arg);
    ~BattleCloseMoveAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
