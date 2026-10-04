#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossWalkAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossWalkAttack, ksys::act::ai::Ai)
public:
    explicit PriestBossWalkAttack(const InitArg& arg);
    ~PriestBossWalkAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAtDirType_s{};
    // static_param at offset 0x40
    const int* mAtAttr_s{};
    // static_param at offset 0x48
    const int* mAtType_s{};
    // static_param at offset 0x50
    const int* mAtShieldBreakPower_s{};
    // static_param at offset 0x58
    const int* mAtImpact_s{};
    // static_param at offset 0x60
    const int* mAtPowerReduce_s{};
    // static_param at offset 0x68
    const int* mAtPower_s{};
    // static_param at offset 0x70
    const int* mAtDamage_s{};
    // static_param at offset 0x78
    const float* mGoalDistanceTolerance_s{};
    // static_param at offset 0x80
    const float* mAngleNeedTurn_s{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mTargetPos_d{};
    // aitree_variable at offset 0x90
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
