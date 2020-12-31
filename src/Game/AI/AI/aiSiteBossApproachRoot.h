#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossApproachRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossApproachRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossApproachRoot(const InitArg& arg);
    ~SiteBossApproachRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCheckWallDist_s{};
    // static_param at offset 0x40
    const float* mApproachTime_s{};
    // static_param at offset 0x48
    const float* mEndDist_s{};
    // static_param at offset 0x50
    const float* mEndFarDist_s{};
    // static_param at offset 0x58
    const float* mAttackStartDist_s{};
    // static_param at offset 0x60
    const bool* mDoAttack_s{};
    // dynamic_param at offset 0x68
    bool* mIsMoveSide_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
