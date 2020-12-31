#pragma once

#include "Game/AI/AI/aiEarthReleaseAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GiantEarthReleaseAttack : public EarthReleaseAttack {
    SEAD_RTTI_OVERRIDE(GiantEarthReleaseAttack, EarthReleaseAttack)
public:
    explicit GiantEarthReleaseAttack(const InitArg& arg);
    ~GiantEarthReleaseAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const float* mStartHeight_s{};
    // static_param at offset 0x98
    const float* mStartDistFromTarget_s{};
    // aitree_variable at offset 0xa0
    float* mKeepDistFromGround_a{};
    // aitree_variable at offset 0xa8
    bool* mIsArrivedAtDestination_a{};
    // aitree_variable at offset 0xb0
    sead::Vector3f* mDestinationPos_a{};
};

}  // namespace uking::ai
