#pragma once

#include "Game/AI/Action/actionBattleCloseMeanderRun.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseMeanderGuardRun : public BattleCloseMeanderRun {
    SEAD_RTTI_OVERRIDE(BattleCloseMeanderGuardRun, BattleCloseMeanderRun)
public:
    explicit BattleCloseMeanderGuardRun(const InitArg& arg);
    ~BattleCloseMeanderGuardRun() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    const float* mMeanderWidth_s{};
    // static_param at offset 0xb0
    const float* mMeanderSpeed_s{};
    // static_param at offset 0xb8
    const float* mJumpUpSpeedReduceRatio_s{};
};

}  // namespace uking::action
