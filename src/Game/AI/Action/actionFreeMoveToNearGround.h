#pragma once

#include "Game/AI/Action/actionFreeMoveToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FreeMoveToNearGround : public FreeMoveToTarget {
    SEAD_RTTI_OVERRIDE(FreeMoveToNearGround, FreeMoveToTarget)
public:
    explicit FreeMoveToNearGround(const InitArg& arg);
    ~FreeMoveToNearGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd0
    const float* mReduceSpeedRateWithWind_s{};
    // static_param at offset 0xd8
    const float* mWindVelocityLimit4Reduce_s{};
};

}  // namespace uking::action
