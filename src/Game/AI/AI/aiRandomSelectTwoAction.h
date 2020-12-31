#pragma once

#include "Game/AI/AI/aiRandomSelectTwoActionBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RandomSelectTwoAction : public RandomSelectTwoActionBase {
    SEAD_RTTI_OVERRIDE(RandomSelectTwoAction, RandomSelectTwoActionBase)
public:
    explicit RandomSelectTwoAction(const InitArg& arg);
    ~RandomSelectTwoAction() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x50
    const int* mTransitionRateToA_s{};
};

}  // namespace uking::ai
