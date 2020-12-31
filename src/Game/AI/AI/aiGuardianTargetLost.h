#pragma once

#include "Game/AI/AI/aiGuardianAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianTargetLost : public GuardianAI {
    SEAD_RTTI_OVERRIDE(GuardianTargetLost, GuardianAI)
public:
    explicit GuardianTargetLost(const InitArg& arg);
    ~GuardianTargetLost() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const int* mLostCountMax_s{};
    // static_param at offset 0x70
    const float* mMoveRange_s{};
    // static_param at offset 0x78
    const float* mBackOffset_s{};
    // static_param at offset 0x80
    const float* mAirThreshold_s{};
};

}  // namespace uking::ai
