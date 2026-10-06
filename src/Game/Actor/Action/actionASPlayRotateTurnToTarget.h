#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ASPlayRotateTurnToTarget : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ASPlayRotateTurnToTarget, ksys::act::ai::Action)
public:
    explicit ASPlayRotateTurnToTarget(const InitArg& arg);
    ~ASPlayRotateTurnToTarget() override;

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
