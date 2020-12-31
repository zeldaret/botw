#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelOnNoNavMeshPos : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelOnNoNavMeshPos, ksys::act::ai::Ai)
public:
    explicit LynelOnNoNavMeshPos(const InitArg& arg);
    ~LynelOnNoNavMeshPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mJumpTimer_s{};
    // static_param at offset 0x40
    const int* mWeaponIdx_s{};
    // static_param at offset 0x48
    const float* mHeavySlopeAngle_s{};
    // static_param at offset 0x50
    const float* mNoJumpDist_s{};
    // static_param at offset 0x58
    const float* mHyperJumpDist_s{};
};

}  // namespace uking::ai
