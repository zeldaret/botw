#pragma once

#include "Game/AI/AI/aiGuardianAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianCloseBattle : public GuardianAI {
    SEAD_RTTI_OVERRIDE(GuardianCloseBattle, GuardianAI)
public:
    explicit GuardianCloseBattle(const InitArg& arg);
    ~GuardianCloseBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
