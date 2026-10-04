#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniRecognizeTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniRecognizeTarget, ksys::act::ai::Ai)
public:
    explicit GuardianMiniRecognizeTarget(const InitArg& arg);
    ~GuardianMiniRecognizeTarget() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
