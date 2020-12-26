#pragma once

#include "Game/AI/Action/actionWaterFloatBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FloatWait : public WaterFloatBase {
    SEAD_RTTI_OVERRIDE(FloatWait, WaterFloatBase)
public:
    explicit FloatWait(const InitArg& arg);
    ~FloatWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const float* mWaterEffectSpeedRate_s{};
    // static_param at offset 0x68
    sead::SafeString mASKeyName_s{};
};

}  // namespace uking::action
