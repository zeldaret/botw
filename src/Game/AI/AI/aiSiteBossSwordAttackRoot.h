#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSwordAttackRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSwordAttackRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossSwordAttackRoot(const InitArg& arg);
    ~SiteBossSwordAttackRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mCloseAttackRate_s{};
    // static_param at offset 0x40
    const int* mChemicalPlusRate_s{};
    // static_param at offset 0x48
    const int* mThrowAttackPower_s{};
    // static_param at offset 0x50
    const int* mAddAttackPower_s{};
    // static_param at offset 0x58
    const int* mThrowMinDamage_s{};
    // static_param at offset 0x60
    const int* mThrowRate_s{};
    // static_param at offset 0x68
    const int* mPillarMax_s{};
    // static_param at offset 0x70
    const int* mElectricCounterMax_s{};
    // static_param at offset 0x78
    const float* mChemicalPlusHPRate_s{};
    // static_param at offset 0x80
    const float* mShieldRepairTime_s{};
    // static_param at offset 0x88
    const float* mFirstAttackHPRate_s{};
    // static_param at offset 0x90
    const float* mSecondAttackHPRate_s{};
    // static_param at offset 0x98
    const float* mBeamAttackHPRate_s{};
    // static_param at offset 0xa0
    const float* mElectricBallScaleTime_s{};
    // static_param at offset 0xa8
    const float* mElectricBallScale_s{};
    // static_param at offset 0xb0
    const float* mElectricBallRange_s{};
    // static_param at offset 0xb8
    const float* mThrowDist_s{};
    // static_param at offset 0xc0
    sead::SafeString mDemoName_s{};
    // static_param at offset 0xd0
    sead::SafeString mEntryPointName_s{};
    // static_param at offset 0xe0
    sead::SafeString mThrowActorName_s{};
    // dynamic_param at offset 0xf0
    bool* mIsCancelAttack_d{};
};

}  // namespace uking::ai
