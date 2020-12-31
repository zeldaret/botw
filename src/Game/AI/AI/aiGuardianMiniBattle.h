#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(GuardianMiniBattle, EnemyBattle)
public:
    explicit GuardianMiniBattle(const InitArg& arg);
    ~GuardianMiniBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    sead::SafeString mRootNodeName_s{};
    // static_param at offset 0xa0
    sead::SafeString mArm1NodeName_s{};
    // static_param at offset 0xb0
    sead::SafeString mArm2NodeName_s{};
    // static_param at offset 0xc0
    sead::SafeString mArm3NodeName_s{};
    // static_param at offset 0xd0
    const int* mASSlotRight_s{};
    // static_param at offset 0xd8
    const int* mASSlotLeft_s{};
    // static_param at offset 0xe0
    const int* mASSlotBack_s{};
    // static_param at offset 0xe8
    const int* mRollingInterval_s{};
    // static_param at offset 0xf0
    const float* mBaseDist_s{};
    // static_param at offset 0xf8
    const float* mFarDist_s{};
    // static_param at offset 0x100
    const bool* mIsIgnoreArmCondition_s{};
    // static_param at offset 0x108
    const int* mTurnMoveTime_s{};
    // static_param at offset 0x110
    const int* mTurnMovePer_s{};
    // static_param at offset 0x118
    const float* mTurnMoveStartDist_s{};
    // static_param at offset 0x120
    const int* mCounterStartDamageCount_s{};
    // static_param at offset 0x128
    const int* mCounterStartTime_s{};
    // static_param at offset 0x130
    const bool* mCheckOnNoNavMesh_s{};
    // aitree_variable at offset 0x138
    int* mDamagedCount_a{};
};

}  // namespace uking::ai
