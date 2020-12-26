#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MotorcycleAppear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MotorcycleAppear, ksys::act::ai::Action)
public:
    explicit MotorcycleAppear(const InitArg& arg);
    ~MotorcycleAppear() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mHideFrames_s{};
    // static_param at offset 0x28
    const float* mModelWarpEffectFrames_s{};
    // static_param at offset 0x30
    const float* mEndFrames_s{};
};

}  // namespace uking::action
