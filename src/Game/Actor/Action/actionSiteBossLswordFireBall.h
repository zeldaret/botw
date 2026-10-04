#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossLswordFireBall : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossLswordFireBall, ksys::act::ai::Action)
public:
    explicit SiteBossLswordFireBall(const InitArg& arg);
    ~SiteBossLswordFireBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAppearInterval_s{};
    // static_param at offset 0x28
    const float* mBallAppearOffset_s{};
    // static_param at offset 0x30
    const float* mFireBallScale_s{};
    // static_param at offset 0x38
    const bool* mIsShowChildDevice_s{};
    // static_param at offset 0x40
    sead::SafeString mWaitASName_s{};
    // dynamic_param at offset 0x50
    sead::SafeString mPartsName_d{};
};

}  // namespace uking::action
