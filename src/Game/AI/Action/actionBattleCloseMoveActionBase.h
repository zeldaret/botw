#pragma once

#include "Game/AI/Action/actionBattleCloseAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseMoveActionBase : public BattleCloseAction {
    SEAD_RTTI_OVERRIDE(BattleCloseMoveActionBase, BattleCloseAction)
public:
    explicit BattleCloseMoveActionBase(const InitArg& arg);
    ~BattleCloseMoveActionBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
