#pragma once

#include "Game/AI/Action/actionBattleCloseExplosivesAvoidRun.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseDangerAvoidRun : public BattleCloseExplosivesAvoidRun {
    SEAD_RTTI_OVERRIDE(BattleCloseDangerAvoidRun, BattleCloseExplosivesAvoidRun)
public:
    explicit BattleCloseDangerAvoidRun(const InitArg& arg);
    ~BattleCloseDangerAvoidRun() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe0
    const float* mAvoidSubAngle_s{};
};

}  // namespace uking::action
