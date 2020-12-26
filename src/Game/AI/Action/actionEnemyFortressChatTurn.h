#pragma once

#include "Game/AI/Action/actionEnemyFortressChatTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressChatTurn : public EnemyFortressChatTurnBase {
    SEAD_RTTI_OVERRIDE(EnemyFortressChatTurn, EnemyFortressChatTurnBase)
public:
    explicit EnemyFortressChatTurn(const InitArg& arg);
    ~EnemyFortressChatTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xc8
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
