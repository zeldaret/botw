#pragma once

#include "Game/AI/Action/actionBattleCloseMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantBattleCloseAction : public BattleCloseMoveAction {
    SEAD_RTTI_OVERRIDE(GiantBattleCloseAction, BattleCloseMoveAction)
public:
    explicit GiantBattleCloseAction(const InitArg& arg);
    ~GiantBattleCloseAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    const float* mVibrationPower_s{};
};

}  // namespace uking::action
