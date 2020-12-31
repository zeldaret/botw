#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseGoToEatAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseGoToEatAI, ksys::act::ai::Ai)
public:
    explicit HorseGoToEatAI(const InitArg& arg);
    ~HorseGoToEatAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mTimeoutFrame_s{};
    // dynamic_param at offset 0x40
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
