#pragma once

#include "Game/Actor/Action/actionEnemyFortressChatLookBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressChatTurn : public EnemyFortressChatLookBase {
    SEAD_RTTI_OVERRIDE(EnemyFortressChatTurn, EnemyFortressChatLookBase)
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
