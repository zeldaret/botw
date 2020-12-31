#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwimEnemyRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwimEnemyRoam, ksys::act::ai::Ai)
public:
    explicit SwimEnemyRoam(const InitArg& arg);
    ~SwimEnemyRoam() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRoamRadius_s{};
    // static_param at offset 0x40
    const float* mRoamRatio_s{};
    // static_param at offset 0x48
    const float* mRoamXRadius_s{};
    // static_param at offset 0x50
    const float* mRoamZRadius_s{};
};

}  // namespace uking::ai
