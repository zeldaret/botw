#pragma once

#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyChaseTargetAndAction : public UnarmedEnemySearch {
    SEAD_RTTI_OVERRIDE(EnemyChaseTargetAndAction, UnarmedEnemySearch)
public:
    explicit EnemyChaseTargetAndAction(const InitArg& arg);
    ~EnemyChaseTargetAndAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const int* mRepathTime_s{};
    // static_param at offset 0x70
    const float* mLostDist_s{};
    // static_param at offset 0x78
    const float* mLostSpeed_s{};
    // static_param at offset 0x80
    const float* mLostAng_s{};
    // dynamic_param at offset 0x88
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
