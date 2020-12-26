#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TargetCircle : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TargetCircle, ksys::act::ai::Action)
public:
    explicit TargetCircle(const InitArg& arg);
    ~TargetCircle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeed_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // static_param at offset 0x30
    const float* mRotDist_s{};
    // dynamic_param at offset 0x38
    int* mRotDir_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
