#pragma once

#include "Game/AI/Action/actionSiteBossBowBlowOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSpearBlownOff : public SiteBossBowBlowOff {
    SEAD_RTTI_OVERRIDE(SiteBossSpearBlownOff, SiteBossBowBlowOff)
public:
    explicit SiteBossSpearBlownOff(const InitArg& arg);
    ~SiteBossSpearBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x190
    const int* mDownTimeAtLater_s{};
};

}  // namespace uking::action
