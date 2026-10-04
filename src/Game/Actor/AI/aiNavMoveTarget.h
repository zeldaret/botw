#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NavMoveTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NavMoveTarget, ksys::act::ai::Ai)
public:
    explicit NavMoveTarget(const InitArg& arg);
    ~NavMoveTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x8];
    // aitree_variable at offset 0x40
    void* mRefPosVibrateCheckerForAI_a{};
    // aitree_variable at offset 0x48
    void* mRefVelRotVibrateCheckerforAI_a{};
    // static_param at offset 0x320
    const int* mWeaponIdx_s{};
    // static_param at offset 0x328
    const float* mReachTargetArea_s{};
    // static_param at offset 0x330
    const float* mRepathTime_s{};
    // static_param at offset 0x338
    const float* mTooFarDist_s{};
    // static_param at offset 0x340
    const bool* mUseCharacterRadius_s{};
    // static_param at offset 0x348
    const int* mVibrateCheckTime_s{};
    // static_param at offset 0x350
    const int* mRotVibrateCheckTime_s{};
    // static_param at offset 0x358
    const bool* mIsLastLineReachCheck_s{};
    // dynamic_param at offset 0x360
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
