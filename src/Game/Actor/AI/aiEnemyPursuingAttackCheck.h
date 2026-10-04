#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyPursuingAttackCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyPursuingAttackCheck, ksys::act::ai::Ai)
public:
    explicit EnemyPursuingAttackCheck(const InitArg& arg);
    ~EnemyPursuingAttackCheck() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mPursuingAttackInterval_s{};
    // static_param at offset 0x40
    const int* mPursuingAttackIntervalRand_s{};
    // static_param at offset 0x48
    const float* mPursuingAttackStartAng_s{};
    // static_param at offset 0x50
    const float* mAttackAng_s{};
};

}  // namespace uking::ai
