#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PullOut : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(PullOut, ActionWithAS)
public:
    explicit PullOut(const InitArg& arg);
    ~PullOut() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const sead::Vector3f* mAnimGrabPos_s{};
    // dynamic_param at offset 0x38
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
