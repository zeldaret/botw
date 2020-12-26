#pragma once

#include "Game/AI/Action/actionWaterFloatImmobile.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OneTimeWaterFloatStopASPlay : public WaterFloatImmobile {
    SEAD_RTTI_OVERRIDE(OneTimeWaterFloatStopASPlay, WaterFloatImmobile)
public:
    explicit OneTimeWaterFloatStopASPlay(const InitArg& arg);
    ~OneTimeWaterFloatStopASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const bool* mIgnoreSameAS_s{};
    // static_param at offset 0x78
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
