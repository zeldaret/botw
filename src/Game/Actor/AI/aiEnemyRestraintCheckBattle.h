#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyRestraintCheckBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRestraintCheckBattle, ksys::act::ai::Ai)
public:
    explicit EnemyRestraintCheckBattle(const InitArg& arg);
    ~EnemyRestraintCheckBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mCheckInterval_s{};
    // static_param at offset 0x40
    const int* mCheckRandTime_s{};
    // static_param at offset 0x48
    const float* mCheckDist_s{};
    // static_param at offset 0x50
    const float* mCheckVmin_s{};
    // static_param at offset 0x58
    const float* mCheckVmax_s{};
    // static_param at offset 0x60
    const float* mCheckAngle_s{};
    // static_param at offset 0x68
    const bool* mIsResetInterval_s{};
};

}  // namespace uking::ai
