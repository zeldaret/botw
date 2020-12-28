#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpMyHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpMyHorse, ksys::act::ai::Action)
public:
    explicit WarpMyHorse(const InitArg& arg);
    ~WarpMyHorse() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    float* mPositionX_d{};
    // dynamic_param at offset 0x28
    float* mPositionY_d{};
    // dynamic_param at offset 0x30
    float* mPositionZ_d{};
    // dynamic_param at offset 0x38
    float* mDirection_d{};
};

}  // namespace uking::action
