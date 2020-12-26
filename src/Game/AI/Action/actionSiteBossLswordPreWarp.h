#pragma once

#include "Game/AI/Action/actionLastBossPreNormalWarp.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossLswordPreWarp : public LastBossPreNormalWarp {
    SEAD_RTTI_OVERRIDE(SiteBossLswordPreWarp, LastBossPreNormalWarp)
public:
    explicit SiteBossLswordPreWarp(const InitArg& arg);
    ~SiteBossLswordPreWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    sead::SafeString mSleepPartsName_s{};
};

}  // namespace uking::action
