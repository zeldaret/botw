#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RandomJump : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RandomJump, ksys::act::ai::Action)
public:
    explicit RandomJump(const InitArg& arg);
    ~RandomJump() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAngleLimit_s{};
    // static_param at offset 0x28
    const float* mHeightMin_s{};
    // static_param at offset 0x30
    const float* mHeightMaxOffset_s{};
    // static_param at offset 0x38
    const float* mDistanceMin_s{};
    // static_param at offset 0x40
    const float* mDistanceMaxOffset_s{};
    // static_param at offset 0x48
    const bool* mIsReturnByHitWall_s{};
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
