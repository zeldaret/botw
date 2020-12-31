#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBeamAttackMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniBeamAttackMove, ksys::act::ai::Ai)
public:
    explicit GuardianMiniBeamAttackMove(const InitArg& arg);
    ~GuardianMiniBeamAttackMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mMoveTime_s{};
    // static_param at offset 0x40
    const int* mAttackInterval_s{};
    // static_param at offset 0x48
    const float* mBeamSpeed_s{};
    // static_param at offset 0x50
    sead::SafeString mBaseNode_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x68
    const float* mTargetDistOffset_s{};
};

}  // namespace uking::ai
