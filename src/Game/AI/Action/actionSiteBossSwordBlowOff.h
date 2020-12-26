#pragma once

#include "Game/AI/Action/actionSiteBossBowBlowOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordBlowOff : public SiteBossBowBlowOff {
    SEAD_RTTI_OVERRIDE(SiteBossSwordBlowOff, SiteBossBowBlowOff)
public:
    explicit SiteBossSwordBlowOff(const InitArg& arg);
    ~SiteBossSwordBlowOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
