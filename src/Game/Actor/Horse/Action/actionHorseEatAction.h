#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseEatAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseEatAction, ksys::act::ai::Action)
public:
    explicit HorseEatAction(const InitArg& arg);
    ~HorseEatAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mTargetDirToStickX_s{};
    // static_param at offset 0x28
    const float* mTargetDistOffset_s{};
    // static_param at offset 0x30
    const float* mTargetDistToStickY_s{};
    // static_param at offset 0x38
    const float* mMaxStickXForEat_s{};
    // static_param at offset 0x40
    const float* mMaxStickYForEat_s{};
    // static_param at offset 0x48
    const float* mDelayFrames_s{};
    // dynamic_param at offset 0x50
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
