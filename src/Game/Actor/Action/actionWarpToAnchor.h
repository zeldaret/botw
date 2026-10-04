#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpToAnchor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpToAnchor, ksys::act::ai::Action)
public:
    explicit WarpToAnchor(const InitArg& arg);
    ~WarpToAnchor() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    float* mDirectionY_d{};
    // dynamic_param at offset 0x28
    float* mDestinationY_d{};
    // dynamic_param at offset 0x30
    float* mDestinationZ_d{};
    // dynamic_param at offset 0x38
    float* mDestinationX_d{};
};

}  // namespace uking::action
