#pragma once

#include "Game/AI/Action/actionGuardianMoveTo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMoveToPosition : public GuardianMoveTo {
    SEAD_RTTI_OVERRIDE(GuardianMoveToPosition, GuardianMoveTo)
public:
    explicit GuardianMoveToPosition(const InitArg& arg);
    ~GuardianMoveToPosition() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const bool* mDecelerate_s{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mDynTargetPos_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mDynStartPos_d{};
};

}  // namespace uking::action
