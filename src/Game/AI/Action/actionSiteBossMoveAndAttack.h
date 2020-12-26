#pragma once

#include "Game/AI/Action/actionSiteBossMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossMoveAndAttack : public SiteBossMove {
    SEAD_RTTI_OVERRIDE(SiteBossMoveAndAttack, SiteBossMove)
public:
    explicit SiteBossMoveAndAttack(const InitArg& arg);
    ~SiteBossMoveAndAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
