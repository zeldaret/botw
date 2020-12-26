#pragma once

#include "Game/AI/Action/actionLastBossPostNormalWarp.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossLswordPostWarp : public LastBossPostNormalWarp {
    SEAD_RTTI_OVERRIDE(SiteBossLswordPostWarp, LastBossPostNormalWarp)
public:
    explicit SiteBossLswordPostWarp(const InitArg& arg);
    ~SiteBossLswordPostWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb8
    sead::SafeString mCancelSleepPartsName_s{};
};

}  // namespace uking::action
