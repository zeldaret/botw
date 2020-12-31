#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseReins : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseReins, ksys::act::ai::Ai)
public:
    explicit HorseReins(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
