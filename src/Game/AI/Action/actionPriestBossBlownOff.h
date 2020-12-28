#pragma once

#include "Game/AI/Action/actionBlownOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossBlownOff : public BlownOff {
    SEAD_RTTI_OVERRIDE(PriestBossBlownOff, BlownOff)
public:
    explicit PriestBossBlownOff(const InitArg& arg);
    ~PriestBossBlownOff() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
