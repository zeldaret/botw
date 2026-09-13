#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseReturnToSafePos : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseReturnToSafePos, ksys::act::ai::Action)
public:
    explicit HorseReturnToSafePos(const InitArg& arg);
    ~HorseReturnToSafePos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mStartFadeOutFrame_s{};
    // static_param at offset 0x28
    const float* mHiddenFrames_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
