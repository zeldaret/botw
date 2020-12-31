#pragma once

#include "Game/AI/AI/aiRangeSelectTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RangeHeightSelectTwoAction : public RangeSelectTwoAction {
    SEAD_RTTI_OVERRIDE(RangeHeightSelectTwoAction, RangeSelectTwoAction)
public:
    explicit RangeHeightSelectTwoAction(const InitArg& arg);
    ~RangeHeightSelectTwoAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x70
    const float* mMaxY_s{};
    // static_param at offset 0x78
    const float* mMinY_s{};
};

}  // namespace uking::ai
