#pragma once

#include "Game/AI/AI/aiRailMoveRemains.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DemoRailMoveRemains : public RailMoveRemains {
    SEAD_RTTI_OVERRIDE(DemoRailMoveRemains, RailMoveRemains)
public:
    explicit DemoRailMoveRemains(const InitArg& arg);
    ~DemoRailMoveRemains() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x80
    float* mDynSpeedScale_d{};
    // dynamic_param at offset 0x88
    float* mDynInitPosByRailRatio_d{};
};

}  // namespace uking::ai
