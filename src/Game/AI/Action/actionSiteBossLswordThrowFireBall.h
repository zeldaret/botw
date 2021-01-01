#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossLswordThrowFireBall : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossLswordThrowFireBall, ksys::act::ai::Action)
public:
    explicit SiteBossLswordThrowFireBall(const InitArg& arg);
    ~SiteBossLswordThrowFireBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInitVelocity_s{};
    // static_param at offset 0x28
    const float* mFireBallAng_s{};
    // static_param at offset 0x30
    const bool* mIsThrowAll_s{};
    // static_param at offset 0x38
    sead::SafeString mThrowASName_s{};
    // static_param at offset 0x48
    sead::SafeString mBindNodeName_s{};
    // dynamic_param at offset 0x58
    bool* mIsThrowChildDevice_d{};
    // dynamic_param at offset 0x60
    sead::SafeString mPartsName_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x78
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
