#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossEyeBeam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossEyeBeam, ksys::act::ai::Ai)
public:
    explicit PriestBossEyeBeam(const InitArg& arg);
    ~PriestBossEyeBeam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAtMinDamage_s{};
    // static_param at offset 0x40
    const int* mAttackPower_s{};
    // static_param at offset 0x48
    const int* mAttackPowerForPlayer_s{};
    // static_param at offset 0x50
    const int* mShotReviseAngleXU_s{};
    // static_param at offset 0x58
    const int* mShotReviseAngleXD_s{};
    // static_param at offset 0x60
    const int* mShotReviseAngleY_s{};
    // static_param at offset 0x68
    const bool* mIsCreateGuardEffect_s{};
    // static_param at offset 0x70
    const bool* mIsChangeable_s{};
    // static_param at offset 0x78
    const sead::Vector3f* mReflectOffset_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mShotOffset_s{};
};

}  // namespace uking::ai
