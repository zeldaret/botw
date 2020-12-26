#pragma once

#include "Game/AI/Action/actionPlayASForAnimalUnit.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AlertNearbyEnemies : public PlayASForAnimalUnit {
    SEAD_RTTI_OVERRIDE(AlertNearbyEnemies, PlayASForAnimalUnit)
public:
    explicit AlertNearbyEnemies(const InitArg& arg);
    ~AlertNearbyEnemies() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const float* mAlertRange_s{};
    // static_param at offset 0x68
    const float* mAlertTime_s{};
    // static_param at offset 0x70
    const float* mNoiseLevel_s{};
    // static_param at offset 0x78
    const bool* mUseNoise_s{};
};

}  // namespace uking::action
