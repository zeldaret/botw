#pragma once

#include "Game/Actor/Action/actionWaterDepthMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterUpDownMove : public WaterDepthMoveBase {
    SEAD_RTTI_OVERRIDE(WaterUpDownMove, WaterDepthMoveBase)
public:
    explicit WaterUpDownMove(const InitArg& arg);
    ~WaterUpDownMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    const float* mStartDepth_s{};
    // static_param at offset 0x90
    const float* mTargetDepth_s{};
};

}  // namespace uking::action
