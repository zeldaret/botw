#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StopJump : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(StopJump, ActionWithPosAngReduce)
public:
    explicit StopJump(const InitArg& arg);
    ~StopJump() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const float* mJumpHeight_s{};
    // static_param at offset 0x38
    sead::SafeString mJumpLoopAS_s{};
    // static_param at offset 0x48
    sead::SafeString mLandingAS_s{};
};

}  // namespace uking::action
