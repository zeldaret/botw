#pragma once

#include "Game/AI/Action/actionWaterFloatBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterFloatImmobile : public WaterFloatBase {
    SEAD_RTTI_OVERRIDE(WaterFloatImmobile, WaterFloatBase)
public:
    explicit WaterFloatImmobile(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x68
    const float* mAngleReduceRatio_s{};
};

}  // namespace uking::action
