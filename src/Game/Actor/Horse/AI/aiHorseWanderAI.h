#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseWanderAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseWanderAI, ksys::act::ai::Ai)
public:
    explicit HorseWanderAI(const InitArg& arg);
    ~HorseWanderAI() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
