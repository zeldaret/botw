#pragma once

#include "Game/AI/Action/actionSiteBossShootNormalArrow.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossShootArrowRain : public SiteBossShootNormalArrow {
    SEAD_RTTI_OVERRIDE(SiteBossShootArrowRain, SiteBossShootNormalArrow)
public:
    explicit SiteBossShootArrowRain(const InitArg& arg);
    ~SiteBossShootArrowRain() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe8
    const int* mArrowType_s{};
};

}  // namespace uking::action
