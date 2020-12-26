#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossPostNormalWarp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossPostNormalWarp, ksys::act::ai::Action)
public:
    explicit LastBossPostNormalWarp(const InitArg& arg);
    ~LastBossPostNormalWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mWaitTime_s{};
    // static_param at offset 0x28
    const bool* mNoCryAnime_s{};
    // static_param at offset 0x30
    const bool* mIsTurnToTarget_s{};
    // static_param at offset 0x38
    const bool* mIsCheckDistFromTarget_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x50
    bool* mIsKeepDisableDraw_d{};
    // dynamic_param at offset 0x58
    bool* mIsPartsActorTgOn_d{};
    // dynamic_param at offset 0x60
    bool* mIsPartsWarpEffectSync_d{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
