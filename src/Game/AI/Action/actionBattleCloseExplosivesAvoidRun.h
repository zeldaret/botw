#pragma once

#include "Game/AI/Action/actionBattleCloseMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseExplosivesAvoidRun : public BattleCloseMoveAction {
    SEAD_RTTI_OVERRIDE(BattleCloseExplosivesAvoidRun, BattleCloseMoveAction)
public:
    explicit BattleCloseExplosivesAvoidRun(const InitArg& arg);
    ~BattleCloseExplosivesAvoidRun() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    const float* mDamageIgnoreDist_s{};
};

}  // namespace uking::action
