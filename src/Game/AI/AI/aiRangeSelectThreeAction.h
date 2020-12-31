#pragma once

#include "Game/AI/AI/aiRangeSelectAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RangeSelectThreeAction : public RangeSelectAction {
    SEAD_RTTI_OVERRIDE(RangeSelectThreeAction, RangeSelectAction)
public:
    explicit RangeSelectThreeAction(const InitArg& arg);
    ~RangeSelectThreeAction() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x58
    const float* mNearDist_s{};
    // static_param at offset 0x60
    const float* mFarDist_s{};
    // static_param at offset 0x68
    const float* mBaseDist_s{};
};

}  // namespace uking::ai
