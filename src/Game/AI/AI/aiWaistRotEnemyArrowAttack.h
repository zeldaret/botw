#pragma once

#include "Game/AI/AI/aiEnemyBaseArrowAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaistRotEnemyArrowAttack : public EnemyBaseArrowAttack {
    SEAD_RTTI_OVERRIDE(WaistRotEnemyArrowAttack, EnemyBaseArrowAttack)
public:
    explicit WaistRotEnemyArrowAttack(const InitArg& arg);
    ~WaistRotEnemyArrowAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    const int* mRandomPredictFrame_s{};
};

}  // namespace uking::ai
