#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FrontierSpotBgmTriggerAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FrontierSpotBgmTriggerAction, ksys::act::ai::Action)
public:
    explicit FrontierSpotBgmTriggerAction(const InitArg& arg);
    ~FrontierSpotBgmTriggerAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mSound_d{};
    // map_unit_param at offset 0x30
    const float* mSpotBgmLifeScaleMargin_m{};
    // map_unit_param at offset 0x38
    const bool* mIsStopWithoutReductionY_m{};
    // map_unit_param at offset 0x40
    sead::SafeString mSound_m{};
    // map_unit_param at offset 0x50
    sead::SafeString mShape_m{};
};

}  // namespace uking::action
