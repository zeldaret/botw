#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonNearAttackOnFloorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonNearAttackOnFloorRoot, ksys::act::ai::Ai)
public:
    explicit GanonNearAttackOnFloorRoot(const InitArg& arg);
    ~GanonNearAttackOnFloorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mNearDist_s{};
    // dynamic_param at offset 0x40
    bool* mIsCounter_d{};
    // dynamic_param at offset 0x48
    bool* mIsPrevBeam_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
