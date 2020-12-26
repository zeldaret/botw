#pragma once

#include "Game/AI/Action/actionSiteBossSwordWhirlSlashChargeBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordWhirlSlashCharge : public SiteBossSwordWhirlSlashChargeBase {
    SEAD_RTTI_OVERRIDE(SiteBossSwordWhirlSlashCharge, SiteBossSwordWhirlSlashChargeBase)
public:
    explicit SiteBossSwordWhirlSlashCharge(const InitArg& arg);
    ~SiteBossSwordWhirlSlashCharge() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
