#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniFinalBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(GuardianMiniFinalBattle, EnemyBattle)
public:
    explicit GuardianMiniFinalBattle(const InitArg& arg);
    ~GuardianMiniFinalBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const int* mASSlotRight_s{};
    // static_param at offset 0x98
    const int* mASSlotLeft_s{};
    // static_param at offset 0xa0
    const int* mASSlotBack_s{};
    // static_param at offset 0xa8
    const int* mAttackHitNum_s{};
    // static_param at offset 0xb0
    const bool* mIsPreAttackMove_s{};
    // static_param at offset 0xb8
    const float* mRotNeckRate_s{};
    // aitree_variable at offset 0xc0
    int* mGuardianMiniChanceTimeState_a{};
};

}  // namespace uking::ai
