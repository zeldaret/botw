#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PowerupRune : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PowerupRune, ksys::act::ai::Action)
public:
    explicit PowerupRune(const InitArg& arg);
    ~PowerupRune() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mRuneType_d{};
};

}  // namespace uking::action
