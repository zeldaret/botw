#pragma once

#include "Game/AI/AI/aiGuardianMiniBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMini2ndBattle : public GuardianMiniBattle {
    SEAD_RTTI_OVERRIDE(GuardianMini2ndBattle, GuardianMiniBattle)
public:
    explicit GuardianMini2ndBattle(const InitArg& arg);
    ~GuardianMini2ndBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1b8
    const int* mAttackHitNum_s{};
    // static_param at offset 0x1c0
    const int* mCounterStopTime_s{};
};

}  // namespace uking::ai
