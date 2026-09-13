#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetFogDirect : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetFogDirect, ksys::act::ai::Action)
public:
    explicit EventSetFogDirect(const InitArg& arg);
    ~EventSetFogDirect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mFogRatio_d{};
    // dynamic_param at offset 0x28
    float* mNear_d{};
    // dynamic_param at offset 0x30
    float* mFar_d{};
    // dynamic_param at offset 0x38
    bool* mNearUse_d{};
    // dynamic_param at offset 0x40
    bool* mInstantSW_d{};
    // dynamic_param at offset 0x48
    bool* mFarUse_d{};
};

}  // namespace uking::action
