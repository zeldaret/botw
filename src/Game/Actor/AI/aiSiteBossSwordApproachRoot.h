#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSwordApproachRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSwordApproachRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossSwordApproachRoot(const InitArg& arg);
    ~SiteBossSwordApproachRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mKeepDistance_s{};
    // static_param at offset 0x40
    const float* mMoveWidth_s{};
    // static_param at offset 0x48
    const float* mBaseOffsetY_s{};
    // static_param at offset 0x50
    const float* mPredictMoveFrame_s{};
    // static_param at offset 0x58
    const bool* mIsCloseMove_s{};
    // static_param at offset 0x60
    const bool* mIsPlayRunStartAS_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mOldTargetPos_d{};
};

}  // namespace uking::ai
