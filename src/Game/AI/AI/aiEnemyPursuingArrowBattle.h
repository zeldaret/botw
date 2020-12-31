#pragma once

#include "Game/AI/AI/aiBokoblinArrowBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyPursuingArrowBattle : public BokoblinArrowBattle {
    SEAD_RTTI_OVERRIDE(EnemyPursuingArrowBattle, BokoblinArrowBattle)
public:
    explicit EnemyPursuingArrowBattle(const InitArg& arg);
    ~EnemyPursuingArrowBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x128
    const int* mPursuingAttackInterval_s{};
    // static_param at offset 0x130
    const int* mPursuingAttackIntervalRand_s{};
    // static_param at offset 0x138
    const float* mPursuingAttackStartDist_s{};
    // static_param at offset 0x140
    const float* mPursuingAttackStartAng_s{};
};

}  // namespace uking::ai
