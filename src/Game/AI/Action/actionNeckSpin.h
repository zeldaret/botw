#pragma once

#include "Game/AI/Action/actionStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NeckSpin : public StopASPlay {
    SEAD_RTTI_OVERRIDE(NeckSpin, StopASPlay)
public:
    explicit NeckSpin(const InitArg& arg);
    ~NeckSpin() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const float* mSpinSpeed_s{};
    // static_param at offset 0x50
    const float* mNeckUDAngle_s{};
};

}  // namespace uking::action
