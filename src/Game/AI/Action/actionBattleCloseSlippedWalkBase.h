#pragma once

#include "Game/AI/Action/actionBattleCloseActionWithAcc.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseSlippedWalkBase : public BattleCloseActionWithAcc {
    SEAD_RTTI_OVERRIDE(BattleCloseSlippedWalkBase, BattleCloseActionWithAcc)
public:
    explicit BattleCloseSlippedWalkBase(const InitArg& arg);
    ~BattleCloseSlippedWalkBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
