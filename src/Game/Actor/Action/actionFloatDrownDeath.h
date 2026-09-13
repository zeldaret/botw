#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FloatDrownDeath : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FloatDrownDeath, ksys::act::ai::Action)
public:
    explicit FloatDrownDeath(const InitArg& arg);
    ~FloatDrownDeath() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mFloatDepth_s{};
    // static_param at offset 0x28
    const float* mFloatSpeed_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
