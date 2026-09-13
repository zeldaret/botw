#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemySyncAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemySyncAttack, ksys::act::ai::Ai)
public:
    explicit EnemySyncAttack(const InitArg& arg);
    ~EnemySyncAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mNormalASSlot_s{};
    // static_param at offset 0x40
    const int* mAttackASSlot_s{};
    // static_param at offset 0x48
    sead::SafeString mRootNodeName_s{};
    // static_param at offset 0x58
    sead::SafeString mAttackNodeName_s{};
    // static_param at offset 0x68
    sead::SafeString mAttackNodeNameWait_s{};
    // static_param at offset 0x78
    sead::SafeString mAttackASName_s{};
    // static_param at offset 0x88
    sead::SafeString mAtNodeName_s{};
    // static_param at offset 0x98
    const float* mJustAvoidCheckLength_s{};
    // static_param at offset 0xa0
    const float* mJustAvoidCheckAngle_s{};
    // static_param at offset 0xa8
    const float* mAttackDistMin_s{};
    // static_param at offset 0xb0
    const float* mAttackDistMax_s{};
    // static_param at offset 0xb8
    const int* mAttackInterval_s{};
    // static_param at offset 0xc0
    const int* mAttackIntervalRand_s{};
};

}  // namespace uking::ai
