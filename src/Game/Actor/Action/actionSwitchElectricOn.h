#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwitchElectricOn : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwitchElectricOn, ksys::act::ai::Action)
public:
    explicit SwitchElectricOn(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mElecReq_s{};
    // static_param at offset 0x28
    const float* mVolReq_s{};
    // static_param at offset 0x30
    const float* mTargetVol_s{};
    // static_param at offset 0x38
    const float* mMinEnergyRate_s{};
    // static_param at offset 0x40
    const bool* mUseSklAnm_s{};
};

}  // namespace uking::action
