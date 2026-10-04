#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniTargetOnScalffold : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniTargetOnScalffold, ksys::act::ai::Ai)
public:
    explicit GuardianMiniTargetOnScalffold(const InitArg& arg);
    ~GuardianMiniTargetOnScalffold() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFarDist_s{};
    // static_param at offset 0x40
    const float* mNearDist_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
