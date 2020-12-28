#pragma once

#include "Game/AI/Action/actionFreeMovingAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HoverBase : public FreeMovingAction {
    SEAD_RTTI_OVERRIDE(HoverBase, FreeMovingAction)
public:
    explicit HoverBase(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    const float* mAngReduceRatio_s{};
};

}  // namespace uking::action
