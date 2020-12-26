#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RotateTurnToTarget : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RotateTurnToTarget, ksys::act::ai::Action)
public:
    explicit RotateTurnToTarget(const InitArg& arg);
    ~RotateTurnToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAngSpd_s{};
    // static_param at offset 0x28
    const bool* mIsJumpType_s{};
    // static_param at offset 0x30
    const bool* mIsChangeable_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
