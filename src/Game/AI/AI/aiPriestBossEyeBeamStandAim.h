#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossEyeBeamStandAim : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossEyeBeamStandAim, ksys::act::ai::Ai)
public:
    explicit PriestBossEyeBeamStandAim(const InitArg& arg);
    ~PriestBossEyeBeamStandAim() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mBorderDist_s{};
    // static_param at offset 0x40
    const float* mBorderHeight_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mAimTargetPos_d{};
};

}  // namespace uking::ai
