#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ApplyMoveTrigger : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ApplyMoveTrigger, ksys::act::ai::Action)
public:
    explicit ApplyMoveTrigger(const InitArg& arg);
    ~ApplyMoveTrigger() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsOnDebugDraw_s{};
    // map_unit_param at offset 0x28
    const int* mTriggerType_m{};
    // map_unit_param at offset 0x30
    const int* mForceType_m{};
    // map_unit_param at offset 0x38
    const float* mApplyForceValue_m{};
};

}  // namespace uking::action
