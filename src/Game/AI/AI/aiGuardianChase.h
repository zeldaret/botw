#pragma once

#include "Game/AI/AI/aiGuardianAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianChase : public GuardianAI {
    SEAD_RTTI_OVERRIDE(GuardianChase, GuardianAI)
public:
    explicit GuardianChase(const InitArg& arg);
    ~GuardianChase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mChaseRange_m{};
};

}  // namespace uking::ai
