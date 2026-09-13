#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BokoblinArrowBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BokoblinArrowBattle, ksys::act::ai::Ai)
public:
    explicit BokoblinArrowBattle(const InitArg& arg);
    ~BokoblinArrowBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mHoldInterval_s{};
    // static_param at offset 0x40
    const int* mHoldIntervalLast_s{};
    // static_param at offset 0x48
    const int* mHoldIntervalRand_s{};
    // static_param at offset 0x50
    const float* mLeaveStartDist_s{};
    // static_param at offset 0x58
    const float* mLeaveEndDist_s{};
    // static_param at offset 0x60
    const int* mLeaveWaitTime_s{};
    // static_param at offset 0x68
    const int* mLeaveTime_s{};
    // static_param at offset 0x70
    const float* mBaseDist_s{};
    // static_param at offset 0x78
    const float* mOutDist_s{};
    // static_param at offset 0x80
    const float* mOutDistVMin_s{};
    // static_param at offset 0x88
    const float* mOutDistVMax_s{};
    // static_param at offset 0x90
    const int* mWeaponIdx_s{};
    // static_param at offset 0x98
    const int* mBlindlyAttackMinNum_s{};
    // static_param at offset 0xa0
    const int* mBlindlyAttackMaxNum_s{};
    // dynamic_param at offset 0xa8
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0xb0
    const float* mShootDistRatio_s{};
    // static_param at offset 0xb8
    const bool* mIsEndAfterAttack_s{};
    // static_param at offset 0xc0
    const bool* mIsUpdateNoticeState_s{};
};

}  // namespace uking::ai
