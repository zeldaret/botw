#pragma once

#include "Game/AI/AI/aiPriestBossEyeBeam.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossEyeBeamFourth : public PriestBossEyeBeam {
    SEAD_RTTI_OVERRIDE(PriestBossEyeBeamFourth, PriestBossEyeBeam)
public:
    explicit PriestBossEyeBeamFourth(const InitArg& arg);
    ~PriestBossEyeBeamFourth() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xb8
    const int* mAtDirType_s{};
    // static_param at offset 0xc0
    const int* mAtAttr_s{};
    // static_param at offset 0xc8
    const int* mAtType_s{};
    // static_param at offset 0xd0
    const int* mAtShieldBreakPower_s{};
    // static_param at offset 0xd8
    const int* mAtImpact_s{};
    // static_param at offset 0xe0
    const int* mAtPowerReduce_s{};
    // static_param at offset 0xe8
    const int* mAtPower_s{};
    // static_param at offset 0xf0
    const int* mAtDamage_s{};
    // static_param at offset 0xf8
    const int* mSearchEndAngle_s{};
    // aitree_variable at offset 0x100
    bool* mIsArrivedAtDestination_a{};
    // aitree_variable at offset 0x108
    sead::Vector3f* mDestinationPos_a{};
    // aitree_variable at offset 0x110
    sead::Vector3f* mFacePos_a{};
    // aitree_variable at offset 0x118
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
