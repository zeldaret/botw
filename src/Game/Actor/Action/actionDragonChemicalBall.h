#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DragonChemicalBall : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DragonChemicalBall, ksys::act::ai::Action)
public:
    explicit DragonChemicalBall(const InitArg& arg);
    ~DragonChemicalBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mLife_s{};
    // static_param at offset 0x28
    const float* mHitScale_s{};
    // static_param at offset 0x30
    const float* mGravity_s{};
    // static_param at offset 0x38
    const float* mHomingPower_s{};
    // static_param at offset 0x40
    const float* mHomingDistance_s{};
    // static_param at offset 0x48
    const float* mHomingTime_s{};
};

}  // namespace uking::action
