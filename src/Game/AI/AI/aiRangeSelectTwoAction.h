#pragma once

#include "Game/AI/AI/aiRangeSelectAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RangeSelectTwoAction : public RangeSelectAction {
    SEAD_RTTI_OVERRIDE(RangeSelectTwoAction, RangeSelectAction)
public:
    explicit RangeSelectTwoAction(const InitArg& arg);
    ~RangeSelectTwoAction() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x58
    const float* mFarDist_s{};
    // static_param at offset 0x60
    const float* mBaseDist_s{};
};

}  // namespace uking::ai
