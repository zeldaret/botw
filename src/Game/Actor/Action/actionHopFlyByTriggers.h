#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HopFlyByTriggers : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HopFlyByTriggers, ksys::act::ai::Action)
public:
    explicit HopFlyByTriggers(const InitArg& arg);
    ~HopFlyByTriggers() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mXZSpeedMax_s{};
    // static_param at offset 0x28
    const float* mHopAccRatio_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
