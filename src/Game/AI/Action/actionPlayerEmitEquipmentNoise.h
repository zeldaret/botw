#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerEmitEquipmentNoise : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerEmitEquipmentNoise, ksys::act::ai::Action)
public:
    explicit PlayerEmitEquipmentNoise(const InitArg& arg);
    ~PlayerEmitEquipmentNoise() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mSteppingFoot_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mSpeed_d{};
};

}  // namespace uking::action
