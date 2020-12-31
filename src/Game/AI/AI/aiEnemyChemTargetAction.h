#pragma once

#include "Game/AI/AI/aiEnemyChemTargetActionBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyChemTargetAction : public EnemyChemTargetActionBase {
    SEAD_RTTI_OVERRIDE(EnemyChemTargetAction, EnemyChemTargetActionBase)
public:
    explicit EnemyChemTargetAction(const InitArg& arg);
    ~EnemyChemTargetAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
