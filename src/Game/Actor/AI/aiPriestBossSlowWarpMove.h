#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossSlowWarpMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossSlowWarpMove, ksys::act::ai::Ai)
public:
    explicit PriestBossSlowWarpMove(const InitArg& arg);
    ~PriestBossSlowWarpMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAfterImage0AppearFrame_s{};
    // static_param at offset 0x40
    const float* mAfterImage1AppearFrame_s{};
    // static_param at offset 0x48
    const float* mAppearFrame_s{};
    // static_param at offset 0x50
    const bool* mTurnFirst_s{};
    // dynamic_param at offset 0x58
    float* mCurrentFrame_d{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mMoveDstPos_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mAfterImage0Pos_d{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mAfterImage1Pos_d{};
};

}  // namespace uking::ai
