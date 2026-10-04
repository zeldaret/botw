#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormCircleMoveTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormCircleMoveTarget, ksys::act::ai::Ai)
public:
    explicit SandwormCircleMoveTarget(const InitArg& arg);
    ~SandwormCircleMoveTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mDirection_s{};
    // static_param at offset 0x40
    const float* mRadius_s{};
    // static_param at offset 0x48
    const float* mRadiusMargin_s{};
    // static_param at offset 0x50
    const float* mSpeed_s{};
    // static_param at offset 0x58
    const float* mFrontCheckLength_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
