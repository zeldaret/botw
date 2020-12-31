#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastBossShootNormalArrowRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossShootNormalArrowRoot, ksys::act::ai::Ai)
public:
    explicit LastBossShootNormalArrowRoot(const InitArg& arg);
    ~LastBossShootNormalArrowRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mArrowNum_s{};
    // static_param at offset 0x40
    const int* mAtMinDamage_s{};
    // static_param at offset 0x48
    const int* mAttackPower_s{};
    // static_param at offset 0x50
    const int* mAttackPowerForPlayer_s{};
    // static_param at offset 0x58
    const float* mBattleNodeOffsetLR_s{};
    // static_param at offset 0x60
    const float* mBattleNodeOffsetUD_s{};
    // static_param at offset 0x68
    const bool* mIsPrepreNextArrow_s{};
    // static_param at offset 0x70
    sead::SafeString mArrowName_s{};
    // static_param at offset 0x80
    sead::SafeString mPartsName_s{};
    // static_param at offset 0x90
    const sead::Vector3f* mReflectOffset_s{};
    // dynamic_param at offset 0x98
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
