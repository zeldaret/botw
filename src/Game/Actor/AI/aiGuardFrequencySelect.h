#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardFrequencySelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardFrequencySelect, ksys::act::ai::Ai)
public:
    explicit GuardFrequencySelect(const InitArg& arg);
    ~GuardFrequencySelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
