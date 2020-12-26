#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerDemoAccelerateHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerDemoAccelerateHorse, ksys::act::ai::Action)
public:
    explicit PlayerDemoAccelerateHorse(const InitArg& arg);
    ~PlayerDemoAccelerateHorse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInputAccelerateFrame_s{};
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
