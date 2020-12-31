#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DangerAvoidFlagSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DangerAvoidFlagSelect, ksys::act::ai::Ai)
public:
    explicit DangerAvoidFlagSelect(const InitArg& arg);
    ~DangerAvoidFlagSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
