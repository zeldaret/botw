#pragma once

#include "Game/AI/AI/aiGuardianAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianWait : public GuardianAI {
    SEAD_RTTI_OVERRIDE(GuardianWait, GuardianAI)
public:
    explicit GuardianWait(const InitArg& arg);
    ~GuardianWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
