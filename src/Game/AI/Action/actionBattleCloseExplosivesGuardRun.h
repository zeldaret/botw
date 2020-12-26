#pragma once

#include "Game/AI/Action/actionBattleCloseExplosivesAvoidRun.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseExplosivesGuardRun : public BattleCloseExplosivesAvoidRun {
    SEAD_RTTI_OVERRIDE(BattleCloseExplosivesGuardRun, BattleCloseExplosivesAvoidRun)
public:
    explicit BattleCloseExplosivesGuardRun(const InitArg& arg);
    ~BattleCloseExplosivesGuardRun() override;

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
