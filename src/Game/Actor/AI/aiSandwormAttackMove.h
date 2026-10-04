#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormAttackMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormAttackMove, ksys::act::ai::Ai)
public:
    explicit SandwormAttackMove(const InitArg& arg);
    ~SandwormAttackMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSecessionDist_s{};
    // static_param at offset 0x40
    const float* mAttackAngle_s{};
    // static_param at offset 0x48
    const float* mDamageAngle_s{};
    // static_param at offset 0x50
    const float* mLostDist_s{};
    // static_param at offset 0x58
    sead::SafeString mDamageBaseNode_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
