#pragma once

#include "Game/AI/Action/actionTargetCircleWalk.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniGuardSideWalk : public TargetCircleWalk {
    SEAD_RTTI_OVERRIDE(GuardianMiniGuardSideWalk, TargetCircleWalk)
public:
    explicit GuardianMiniGuardSideWalk(const InitArg& arg);
    ~GuardianMiniGuardSideWalk() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const int* mASSlot_s{};
    // static_param at offset 0x88
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
