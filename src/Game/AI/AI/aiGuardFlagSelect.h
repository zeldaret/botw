#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardFlagSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardFlagSelect, ksys::act::ai::Ai)
public:
    explicit GuardFlagSelect(const InitArg& arg);
    ~GuardFlagSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
