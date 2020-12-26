#pragma once

#include "Game/AI/Action/actionFreeMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FreeMoveToTarget : public FreeMove {
    SEAD_RTTI_OVERRIDE(FreeMoveToTarget, FreeMove)
public:
    explicit FreeMoveToTarget(const InitArg& arg);
    ~FreeMoveToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    const int* mTargetUpdateInterval_s{};
    // static_param at offset 0xb0
    const float* mFinishRadius_s{};
    // dynamic_param at offset 0xb8
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
