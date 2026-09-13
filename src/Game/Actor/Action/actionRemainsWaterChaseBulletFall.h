#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsWaterChaseBulletFall : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainsWaterChaseBulletFall, ksys::act::ai::Action)
public:
    explicit RemainsWaterChaseBulletFall(const InitArg& arg);
    ~RemainsWaterChaseBulletFall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mEndTimer_s{};
    // static_param at offset 0x28
    const float* mInWaterDepth_s{};
    // static_param at offset 0x30
    const float* mSetVelocity_s{};
    // static_param at offset 0x38
    const float* mSetVelocityFromWeapon_s{};
};

}  // namespace uking::action
