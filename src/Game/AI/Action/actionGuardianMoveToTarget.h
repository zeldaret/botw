#pragma once

#include "Game/AI/Action/actionGuardianMoveTo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMoveToTarget : public GuardianMoveTo {
    SEAD_RTTI_OVERRIDE(GuardianMoveToTarget, GuardianMoveTo)
public:
    explicit GuardianMoveToTarget(const InitArg& arg);
    ~GuardianMoveToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x28
    const float* mSpeed_s{};
};

}  // namespace uking::action
