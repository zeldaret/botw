#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerWarpEffectValueSetter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerWarpEffectValueSetter, ksys::act::ai::Action)
public:
    explicit PlayerWarpEffectValueSetter(const InitArg& arg);
    ~PlayerWarpEffectValueSetter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mChangeType_d{};
    // dynamic_param at offset 0x28
    float* mSetFrame_d{};
};

}  // namespace uking::action
