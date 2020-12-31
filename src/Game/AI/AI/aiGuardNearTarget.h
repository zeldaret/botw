#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardNearTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardNearTarget, ksys::act::ai::Ai)
public:
    explicit GuardNearTarget(const InitArg& arg);
    ~GuardNearTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mBaseDist_s{};
    // static_param at offset 0x48
    const float* mGuardStartDist_s{};
    // static_param at offset 0x50
    const float* mGuardEndDist_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
