#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossLswordFirstCreateFBall : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossLswordFirstCreateFBall, ksys::act::ai::Action)
public:
    explicit SiteBossLswordFirstCreateFBall(const InitArg& arg);
    ~SiteBossLswordFirstCreateFBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtMinDamage_s{};
    // static_param at offset 0x28
    const int* mAttackPower_s{};
    // static_param at offset 0x30
    const int* mCreateNum_s{};
    // static_param at offset 0x38
    const int* mAddAttackPower_s{};
    // static_param at offset 0x40
    const float* mFireBallScale_s{};
    // static_param at offset 0x48
    sead::SafeString mThrowActorName_s{};
    // static_param at offset 0x58
    sead::SafeString mASName_s{};
    // static_param at offset 0x68
    const sead::Vector3f* mBindPosOffset_s{};
};

}  // namespace uking::action
