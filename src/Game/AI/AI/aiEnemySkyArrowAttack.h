#pragma once

#include "Game/AI/AI/aiEnemyBaseArrowAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemySkyArrowAttack : public EnemyBaseArrowAttack {
    SEAD_RTTI_OVERRIDE(EnemySkyArrowAttack, EnemyBaseArrowAttack)
public:
    explicit EnemySkyArrowAttack(const InitArg& arg);
    ~EnemySkyArrowAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
