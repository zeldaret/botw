#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniTransformSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniTransformSelect, ksys::act::ai::Ai)
public:
    explicit GuardianMiniTransformSelect(const InitArg& arg);
    ~GuardianMiniTransformSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    bool* mIsTransformedGuardianMini_a{};
};

}  // namespace uking::ai
