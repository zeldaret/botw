#pragma once

#include "Game/AI/AI/aiViewWait.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ViewWaitRiskAvoid : public ViewWait {
    SEAD_RTTI_OVERRIDE(ViewWaitRiskAvoid, ViewWait)
public:
    explicit ViewWaitRiskAvoid(const InitArg& arg);
    ~ViewWaitRiskAvoid() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const int* mAvoidFrame_s{};
    // static_param at offset 0x68
    const float* mFrontAngle_s{};
    // static_param at offset 0x70
    const float* mSpaceAngle_s{};
    // static_param at offset 0x78
    const float* mSpaceDist_s{};
};

}  // namespace uking::ai
