#pragma once

#include "Game/AI/Action/actionBattleCloseAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseActionWithAcc : public BattleCloseAction {
    SEAD_RTTI_OVERRIDE(BattleCloseActionWithAcc, BattleCloseAction)
public:
    explicit BattleCloseActionWithAcc(const InitArg& arg);
    ~BattleCloseActionWithAcc() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x98
    const float* mAccRatio_s{};
};

}  // namespace uking::action
