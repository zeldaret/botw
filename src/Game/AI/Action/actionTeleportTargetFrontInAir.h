#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TeleportTargetFrontInAir : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TeleportTargetFrontInAir, ksys::act::ai::Action)
public:
    explicit TeleportTargetFrontInAir(const InitArg& arg);
    ~TeleportTargetFrontInAir() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const float* mTerritoryArea_m{};
    // static_param at offset 0x28
    const float* mDistMin_s{};
    // static_param at offset 0x30
    const float* mDistMax_s{};
    // static_param at offset 0x38
    const float* mFrontAngle_s{};
    // static_param at offset 0x40
    const float* mHeightOffset_s{};
    // static_param at offset 0x48
    const float* mTerritoryArea_s{};
};

}  // namespace uking::action
