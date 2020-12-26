#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveToTargetCurveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MoveToTargetCurveBase, ksys::act::ai::Action)
public:
    explicit MoveToTargetCurveBase(const InitArg& arg);
    ~MoveToTargetCurveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxHeight_s{};
    // static_param at offset 0x28
    const float* mTimeScale_s{};
    // static_param at offset 0x30
    const bool* mIsDebugDrawTargetPos_s{};
};

}  // namespace uking::action
