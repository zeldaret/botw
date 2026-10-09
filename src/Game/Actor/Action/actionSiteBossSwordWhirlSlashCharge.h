#pragma once

#include "Game/Actor/Action/actionLastBossSwordWhirlSlashChargeBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordWhirlSlashCharge : public LastBossSwordWhirlSlashChargeBase {
    SEAD_RTTI_OVERRIDE(SiteBossSwordWhirlSlashCharge, LastBossSwordWhirlSlashChargeBase)
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
