#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyCutRope : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyCutRope, ksys::act::ai::Ai)
public:
    explicit EnemyCutRope(const InitArg& arg);
    ~EnemyCutRope() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mCutDist_s{};
    // static_param at offset 0x48
    const float* mCutAngle_s{};
    // static_param at offset 0x50
    const bool* mCutFlyAttack_s{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
