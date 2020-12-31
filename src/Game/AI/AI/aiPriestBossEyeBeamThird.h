#pragma once

#include "Game/AI/AI/aiPriestBossEyeBeam.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossEyeBeamThird : public PriestBossEyeBeam {
    SEAD_RTTI_OVERRIDE(PriestBossEyeBeamThird, PriestBossEyeBeam)
public:
    explicit PriestBossEyeBeamThird(const InitArg& arg);
    ~PriestBossEyeBeamThird() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0xb8
    bool* mIsArrivedAtDestination_a{};
    // aitree_variable at offset 0xc0
    sead::Vector3f* mDestinationPos_a{};
    // aitree_variable at offset 0xc8
    sead::Vector3f* mFacePos_a{};
};

}  // namespace uking::ai
