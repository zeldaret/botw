#pragma once

#include "Game/AI/Action/actionFreeMovingAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkFlyToTargetDirect : public FreeMovingAction {
    SEAD_RTTI_OVERRIDE(ForkFlyToTargetDirect, FreeMovingAction)
public:
    explicit ForkFlyToTargetDirect(const InitArg& arg);
    ~ForkFlyToTargetDirect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const float* mFinRadius_s{};
    // static_param at offset 0x38
    const float* mMoveSpd_s{};
    // static_param at offset 0x40
    const bool* mOnEndForceStop_s{};
    // static_param at offset 0x48
    const bool* mOnGround_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
