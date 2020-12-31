#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PracticeGuardianMiniNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PracticeGuardianMiniNormal, ksys::act::ai::Ai)
public:
    explicit PracticeGuardianMiniNormal(const InitArg& arg);
    ~PracticeGuardianMiniNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    int* mGuardianMiniPracticeState_a{};
};

}  // namespace uking::ai
