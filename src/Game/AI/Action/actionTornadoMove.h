#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TornadoMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TornadoMove, ksys::act::ai::Action)
public:
    explicit TornadoMove(const InitArg& arg);
    ~TornadoMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxAmplitude_s{};
    // static_param at offset 0x28
    const float* mMinAmplitude_s{};
    // static_param at offset 0x30
    const float* mMaxSpeed_s{};
    // static_param at offset 0x38
    const float* mAmplitudeAddRate_s{};
    // static_param at offset 0x40
    const float* mDeleteTimer_s{};
    // static_param at offset 0x48
    const float* mFrequency_s{};
    // static_param at offset 0x50
    const float* mIgnoreHitFrame_s{};
};

}  // namespace uking::action
