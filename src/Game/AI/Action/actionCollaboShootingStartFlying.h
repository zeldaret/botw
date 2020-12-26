#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CollaboShootingStartFlying : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CollaboShootingStartFlying, ksys::act::ai::Action)
public:
    explicit CollaboShootingStartFlying(const InitArg& arg);
    ~CollaboShootingStartFlying() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInitialVelocityMax_s{};
    // static_param at offset 0x28
    const float* mInitialVelocityMin_s{};
    // static_param at offset 0x30
    const float* mLookSuccessRate_s{};
    // aitree_variable at offset 0x38
    sead::SafeString* mCollaboShootingStarId_a{};
};

}  // namespace uking::action
