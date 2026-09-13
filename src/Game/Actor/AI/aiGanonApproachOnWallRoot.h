#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonApproachOnWallRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonApproachOnWallRoot, ksys::act::ai::Ai)
public:
    explicit GanonApproachOnWallRoot(const InitArg& arg);
    ~GanonApproachOnWallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mApproachTime_s{};
    // static_param at offset 0x40
    const float* mMinDist_s{};
    // static_param at offset 0x48
    const float* mMaxDist_s{};
    // static_param at offset 0x50
    const float* mFinDist_s{};
    // static_param at offset 0x58
    const bool* mIsInterpolateYUp_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
