#pragma once

#include "Game/AI/AI/aiGolemRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemRoot : public GolemRootBase {
    SEAD_RTTI_OVERRIDE(GolemRoot, GolemRootBase)
public:
    explicit GolemRoot(const InitArg& arg);
    ~GolemRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x310
    const int* mClimbFinishTime_s{};
    // static_param at offset 0x318
    const float* mStandContactHeight_s{};
    // static_param at offset 0x320
    const bool* mIsBreakContactTree_s{};
    // map_unit_param at offset 0x328
    sead::SafeString mGolemWeakPointLocation_m{};
    // map_unit_param at offset 0x338
    sead::SafeString mGolemSleepType_m{};
    // map_unit_param at offset 0x348
    sead::SafeString mGolemWeakPointActor_m{};
    // aitree_variable at offset 0x358
    float* mGolemClimbedTime_a{};
};

}  // namespace uking::ai
