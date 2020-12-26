#pragma once

#include "Game/AI/Action/actionBackStepBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackStep : public BackStepBase {
    SEAD_RTTI_OVERRIDE(BackStep, BackStepBase)
public:
    explicit BackStep(const InitArg& arg);
    ~BackStep() override;

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
