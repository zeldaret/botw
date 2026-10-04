#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WillBallFollowAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WillBallFollowAttack, ksys::act::ai::Ai)
public:
    explicit WillBallFollowAttack(const InitArg& arg);
    ~WillBallFollowAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mImmidiateLightningTime_s{};
    // static_param at offset 0x40
    const int* mCycleY_s{};
    // static_param at offset 0x48
    const int* mDelayTimer_s{};
    // static_param at offset 0x50
    const float* mImmidiateLightningXZ_s{};
    // static_param at offset 0x58
    const float* mImmidiateLightningY_s{};
    // static_param at offset 0x60
    const float* mAmplitudeY_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mCenterPos_d{};
};

}  // namespace uking::ai
