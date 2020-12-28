#pragma once

#include "Game/AI/Action/actionLinearFlyAttackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LinearFlyAttack : public LinearFlyAttackBase {
    SEAD_RTTI_OVERRIDE(LinearFlyAttack, LinearFlyAttackBase)
public:
    explicit LinearFlyAttack(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
