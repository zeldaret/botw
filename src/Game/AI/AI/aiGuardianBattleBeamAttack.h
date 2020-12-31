#pragma once

#include "Game/AI/AI/aiGuardianAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianBattleBeamAttack : public GuardianAI {
    SEAD_RTTI_OVERRIDE(GuardianBattleBeamAttack, GuardianAI)
public:
    explicit GuardianBattleBeamAttack(const InitArg& arg);
    ~GuardianBattleBeamAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
