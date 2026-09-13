#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ReflectThrown : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ReflectThrown, ksys::act::ai::Action)
public:
    explicit ReflectThrown(const InitArg& arg);
    ~ReflectThrown() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mReactionLevel_s{};
    // static_param at offset 0x28
    const float* mFinishWaterDepth_s{};
    // dynamic_param at offset 0x30
    float* mPower_d{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetDir_d{};
    // aitree_variable at offset 0x40
    bool* mIsReflectThrownBullet_a{};
};

}  // namespace uking::action
