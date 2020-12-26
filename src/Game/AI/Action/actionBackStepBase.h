#pragma once

#include "Game/AI/Action/actionBackStepToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackStepBase : public BackStepToTarget {
    SEAD_RTTI_OVERRIDE(BackStepBase, BackStepToTarget)
public:
    explicit BackStepBase(const InitArg& arg);
    ~BackStepBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const float* mJumpDist_s{};
};

}  // namespace uking::action
