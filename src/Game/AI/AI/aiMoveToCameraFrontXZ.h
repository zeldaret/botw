#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MoveToCameraFrontXZ : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MoveToCameraFrontXZ, ksys::act::ai::Ai)
public:
    explicit MoveToCameraFrontXZ(const InitArg& arg);
    ~MoveToCameraFrontXZ() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mReverseTimer_s{};
    // static_param at offset 0x40
    const int* mReverseCount_s{};
    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
    // static_param at offset 0x50
    const float* mDistFromPlayer_s{};
    // static_param at offset 0x58
    const float* mMinDistFromPlayer_s{};
    // static_param at offset 0x60
    const float* mAvoidPlayerDist_s{};
    // static_param at offset 0x68
    const float* mAddLineCheckNavRadius_s{};
    // static_param at offset 0x70
    const float* mReachableRadius_s{};
    // static_param at offset 0x78
    const bool* mIsSuccessByLineReachable_s{};
};

}  // namespace uking::ai
