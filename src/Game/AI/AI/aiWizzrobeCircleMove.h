#pragma once

#include "Game/AI/AI/aiCircleMoveTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WizzrobeCircleMove : public CircleMoveTarget {
    SEAD_RTTI_OVERRIDE(WizzrobeCircleMove, CircleMoveTarget)
public:
    explicit WizzrobeCircleMove(const InitArg& arg);
    ~WizzrobeCircleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const float* mFinRadius_s{};
    // static_param at offset 0x70
    const float* mRadiusTimer_s{};
    // static_param at offset 0x78
    const float* mEndTimer_s{};
    // static_param at offset 0x80
    const bool* mIsAttCentral_s{};
};

}  // namespace uking::ai
