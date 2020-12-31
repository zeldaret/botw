#pragma once

#include "Game/AI/AI/aiReflectableThrown.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ReflectableBulletThrown : public ReflectableThrown {
    SEAD_RTTI_OVERRIDE(ReflectableBulletThrown, ReflectableThrown)
public:
    explicit ReflectableBulletThrown(const InitArg& arg);
    ~ReflectableBulletThrown() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0xa8
    float* mPower_d{};
    // dynamic_param at offset 0xb0
    bool* mIsShootByPlayer_d{};
    // dynamic_param at offset 0xb8
    sead::Vector3f* mTargetDir_d{};
    // static_param at offset 0xc0
    const float* mReclectSpd_s{};
};

}  // namespace uking::ai
