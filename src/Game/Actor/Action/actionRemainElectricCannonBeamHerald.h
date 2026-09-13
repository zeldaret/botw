#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainElectricCannonBeamHerald : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainElectricCannonBeamHerald, ksys::act::ai::Action)
public:
    explicit RemainElectricCannonBeamHerald(const InitArg& arg);
    ~RemainElectricCannonBeamHerald() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mHeraldTime_s{};
    // dynamic_param at offset 0x28
    bool* mWillBeProtected_d{};
};

}  // namespace uking::action
