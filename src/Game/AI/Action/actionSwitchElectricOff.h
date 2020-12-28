#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwitchElectricOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwitchElectricOff, ksys::act::ai::Action)
public:
    explicit SwitchElectricOff(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mVolReq_s{};
    // static_param at offset 0x28
    const float* mTargetVol_s{};
    // static_param at offset 0x30
    const bool* mUseSklAnm_s{};
};

}  // namespace uking::action
