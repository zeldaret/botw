#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TurnForLookingAround : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TurnForLookingAround, ksys::act::ai::Ai)
public:
    explicit TurnForLookingAround(const InitArg& arg);
    ~TurnForLookingAround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAngle_s{};
};

}  // namespace uking::ai
