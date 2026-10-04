#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ImmediateStopOwnedHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ImmediateStopOwnedHorse, ksys::act::ai::Action)
public:
    explicit ImmediateStopOwnedHorse(const InitArg& arg);
    ~ImmediateStopOwnedHorse() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mResetChargeNum_d{};
};

}  // namespace uking::action
