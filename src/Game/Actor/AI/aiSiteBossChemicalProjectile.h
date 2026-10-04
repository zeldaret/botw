#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossChemicalProjectile : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossChemicalProjectile, ksys::act::ai::Ai)
public:
    explicit SiteBossChemicalProjectile(const InitArg& arg);
    ~SiteBossChemicalProjectile() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mExplosionTime_s{};
    // static_param at offset 0x40
    const float* mChaseAngleLimit_s{};
    // static_param at offset 0x48
    const float* mReflectSpeedRate_s{};
    // static_param at offset 0x50
    const bool* mIsForceDelete_s{};
    // static_param at offset 0x58
    const bool* mIsAdjustHeight_s{};
    // static_param at offset 0x60
    const bool* mIsSetParentSystemGroupHandler_s{};
    // static_param at offset 0x68
    const bool* mIsSetBindSpeed_s{};
    // static_param at offset 0x70
    const bool* mIsIgnoreObject_s{};
    // static_param at offset 0x78
    sead::SafeString mBindNodeName_s{};
    // map_unit_param at offset 0x88
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x90
    const int* mAtMinDamage_m{};
    // map_unit_param at offset 0x98
    const float* mScaleTime_m{};
    // map_unit_param at offset 0xa0
    const float* mRange_m{};
    // map_unit_param at offset 0xa8
    const float* mAtkRadiusMax_m{};
};

}  // namespace uking::ai
