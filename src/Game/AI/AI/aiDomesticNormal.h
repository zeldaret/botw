#pragma once

#include "Game/AI/AI/aiPreyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DomesticNormal : public PreyNormal {
    SEAD_RTTI_OVERRIDE(DomesticNormal, PreyNormal)
public:
    explicit DomesticNormal(const InitArg& arg);
    ~DomesticNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x340
    const int* mWaitFramesAfterRunMax_s{};
    // static_param at offset 0x348
    const int* mNumFailPathHomeFadeout_s{};
    // static_param at offset 0x350
    const float* mDistUntilReturnToHomePos_s{};
    // static_param at offset 0x358
    const float* mWaitFramesAfterRunMin_s{};
    // static_param at offset 0x360
    const float* mStaggerVelocityThreshold_s{};
    // static_param at offset 0x368
    const float* mDistHomePosFadeout_s{};
    // aitree_variable at offset 0x370
    sead::SafeString* mDomesticAnimalRailName_a{};
};

}  // namespace uking::ai
