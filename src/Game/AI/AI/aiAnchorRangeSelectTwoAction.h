#pragma once

#include "Game/AI/AI/aiRangeSelectTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnchorRangeSelectTwoAction : public RangeSelectTwoAction {
    SEAD_RTTI_OVERRIDE(AnchorRangeSelectTwoAction, RangeSelectTwoAction)
public:
    explicit AnchorRangeSelectTwoAction(const InitArg& arg);
    ~AnchorRangeSelectTwoAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x70
    const float* mFarDist_s{};
    // static_param at offset 0x78
    sead::SafeString mAnchorName_s{};
};

}  // namespace uking::ai
