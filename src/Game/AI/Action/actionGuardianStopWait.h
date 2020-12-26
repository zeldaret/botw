#pragma once

#include "Game/AI/Action/actionGuardianMoveTo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianStopWait : public GuardianMoveTo {
    SEAD_RTTI_OVERRIDE(GuardianStopWait, GuardianMoveTo)
public:
    explicit GuardianStopWait(const InitArg& arg);
    ~GuardianStopWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x28
    const float* mSpeed_s{};
    // dynamic_param at offset 0x30
    float* mDynStopTime_d{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mDynStopPos_d{};
};

}  // namespace uking::action
