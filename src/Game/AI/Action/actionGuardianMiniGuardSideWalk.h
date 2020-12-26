#pragma once

#include "Game/AI/Action/actionTargetCircleWalk.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniGuardSideWalk : public TargetCircleWalk {
    SEAD_RTTI_OVERRIDE(GuardianMiniGuardSideWalk, TargetCircleWalk)
public:
    explicit GuardianMiniGuardSideWalk(const InitArg& arg);
    ~GuardianMiniGuardSideWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x80
    const int* mASSlot_s{};
    // static_param at offset 0x88
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
