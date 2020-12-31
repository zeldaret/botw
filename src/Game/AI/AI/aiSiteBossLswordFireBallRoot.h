#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossLswordFireBallRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossLswordFireBallRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossLswordFireBallRoot(const InitArg& arg);
    ~SiteBossLswordFireBallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mPredictPosRate_s{};
    // static_param at offset 0x40
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x48
    const float* mKeepDistance_s{};
    // static_param at offset 0x50
    const float* mMoveSpeed_s{};
    // static_param at offset 0x58
    const float* mYOffset_s{};
    // static_param at offset 0x60
    const bool* mIsThrowChildDevice_s{};
    // static_param at offset 0x68
    const bool* mIsNeedCreateChildDevice_s{};
    // static_param at offset 0x70
    const sead::Vector3f* mBindPosOffset_s{};
    // dynamic_param at offset 0x78
    sead::SafeString* mThrowActorName_d{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x90
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
