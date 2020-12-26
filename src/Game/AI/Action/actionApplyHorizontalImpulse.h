#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ApplyHorizontalImpulse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ApplyHorizontalImpulse, ksys::act::ai::Action)
public:
    explicit ApplyHorizontalImpulse(const InitArg& arg);
    ~ApplyHorizontalImpulse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::Vector3f* mDynVel_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mDynAngVel_d{};
    // map_unit_param at offset 0x30
    const bool* mIsBreakable_m{};
    // map_unit_param at offset 0x38
    const bool* mEnableToEmitSpEffect_m{};
};

}  // namespace uking::action
