#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetRainSplashRatio : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetRainSplashRatio, ksys::act::ai::Action)
public:
    explicit EventSetRainSplashRatio(const InitArg& arg);
    ~EventSetRainSplashRatio() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mRainSplashRatio_d{};
};

}  // namespace uking::action
