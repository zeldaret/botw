#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Windmill_Wing : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Windmill_Wing, ksys::act::ai::Action)
public:
    explicit Windmill_Wing(const InitArg& arg);
    ~Windmill_Wing() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mStartFrameRange_s{};
    // static_param at offset 0x28
    const float* mASPlaySpeedMin_s{};
    // static_param at offset 0x30
    const float* mASPlaySpeedMax_s{};
    // static_param at offset 0x38
    const float* mASPlaySpeedMinWindPower_s{};
    // static_param at offset 0x40
    const float* mASPlaySpeedMaxWindPower_s{};
    // static_param at offset 0x48
    const float* mTurnRate_s{};
    // static_param at offset 0x50
    const bool* mIsTurnToWindDir_s{};
};

}  // namespace uking::action
