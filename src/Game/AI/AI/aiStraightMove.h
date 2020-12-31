#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StraightMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StraightMove, ksys::act::ai::Ai)
public:
    explicit StraightMove(const InitArg& arg);
    ~StraightMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAngleLimit_s{};
    // static_param at offset 0x40
    const float* mDistanceMax_s{};
    // static_param at offset 0x48
    const float* mDistanceMin_s{};
    // static_param at offset 0x50
    const float* mRetryAngleMax_s{};
    // static_param at offset 0x58
    const float* mRetryAngleMin_s{};
    // static_param at offset 0x60
    const bool* mIsRetryMove_s{};
};

}  // namespace uking::ai
