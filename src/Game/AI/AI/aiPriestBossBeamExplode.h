#pragma once

#include "Game/AI/AI/aiBeamExplodeEitherHit.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossBeamExplode : public BeamExplodeEitherHit {
    SEAD_RTTI_OVERRIDE(PriestBossBeamExplode, BeamExplodeEitherHit)
public:
    explicit PriestBossBeamExplode(const InitArg& arg);
    ~PriestBossBeamExplode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const float* mMaxDistance_s{};
    // static_param at offset 0x68
    const int* mMaxDistanceChangeableBorder_s{};
    // static_param at offset 0x70
    const int* mMaxDistanceChangeableRevise_s{};
};

}  // namespace uking::ai
