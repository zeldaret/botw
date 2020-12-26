#pragma once

#include "Game/AI/Action/actionGiantBattleCloseAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantBattleCloseWalk : public GiantBattleCloseAction {
    SEAD_RTTI_OVERRIDE(GiantBattleCloseWalk, GiantBattleCloseAction)
public:
    explicit GiantBattleCloseWalk(const InitArg& arg);
    ~GiantBattleCloseWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
