#pragma once

#include "Game/AI/AI/aiGuardianAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianDown : public GuardianAI {
    SEAD_RTTI_OVERRIDE(GuardianDown, GuardianAI)
public:
    explicit GuardianDown(const InitArg& arg);
    ~GuardianDown() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
