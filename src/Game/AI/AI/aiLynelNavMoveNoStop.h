#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelNavMoveNoStop : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelNavMoveNoStop, ksys::act::ai::Ai)
public:
    explicit LynelNavMoveNoStop(const InitArg& arg);
    ~LynelNavMoveNoStop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mReachTargetArea_s{};
    // static_param at offset 0x48
    const float* mRepathTime_s{};
    // static_param at offset 0x50
    const float* mTooFarDist_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
