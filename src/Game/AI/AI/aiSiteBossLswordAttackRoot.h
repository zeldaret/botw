#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossLswordAttackRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossLswordAttackRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossLswordAttackRoot(const InitArg& arg);
    ~SiteBossLswordAttackRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mHighSlashRate_s{};
    // static_param at offset 0x40
    const int* mWhirlSlashRate_s{};
    // static_param at offset 0x48
    const int* mFireBallRate_s{};
    // static_param at offset 0x50
    const int* mCrossSlashRate_s{};
    // static_param at offset 0x58
    const int* mTornadoAttackRate_s{};
    // static_param at offset 0x60
    const float* mChemicalPlusHPRate_s{};
    // static_param at offset 0x68
    const float* mIsFarDist_s{};
    // static_param at offset 0x70
    const float* mPatternShiftFirstLifeRate_s{};
    // static_param at offset 0x78
    const float* mReturnWaitCount_s{};
    // static_param at offset 0x80
    const float* mForceApproachCount_s{};
    // dynamic_param at offset 0x88
    bool* mIsAttackPatternFixed_d{};
    // dynamic_param at offset 0x90
    bool* mIsCancelAttack_d{};
};

}  // namespace uking::ai
