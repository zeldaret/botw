#pragma once

#include "Game/Actor/Action/actionGuardianActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMoveToTarget : public GuardianActionBase {
    SEAD_RTTI_OVERRIDE(GuardianMoveToTarget, GuardianActionBase)
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
