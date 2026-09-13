#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayASForDemo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayASForDemo, ksys::act::ai::Action)
public:
    explicit PlayASForDemo(const InitArg& arg);
    ~PlayASForDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAnimeDrivenSettings_s{};
    // dynamic_param at offset 0x28
    int* mTargetIndex_d{};
    // dynamic_param at offset 0x30
    int* mSeqBank_d{};
    // dynamic_param at offset 0x38
    int* mIsEnabledAnimeDriven_d{};
    // dynamic_param at offset 0x40
    int* mClothWarpMode_d{};
    // dynamic_param at offset 0x48
    float* mMorphingFrame_d{};
    // dynamic_param at offset 0x50
    bool* mIsIgnoreSame_d{};
    // dynamic_param at offset 0x58
    sead::SafeString mASName_d{};
};

}  // namespace uking::action
