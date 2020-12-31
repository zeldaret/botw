#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RailMoveRemains : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RailMoveRemains, ksys::act::ai::Ai)
public:
    explicit RailMoveRemains(const InitArg& arg);
    ~RailMoveRemains() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mReactivateTime_s{};
    // static_param at offset 0x40
    const float* mFrontCheckMinDist_s{};
    // static_param at offset 0x48
    const float* mFrontDirUpdateInterval_s{};
    // static_param at offset 0x50
    const float* mSpeedScale_s{};
    // static_param at offset 0x58
    const float* mInitPosByRailRatio_s{};
};

}  // namespace uking::ai
