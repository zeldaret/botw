#pragma once

#include "Game/Actor/Action/actionFlyingActorDamageBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyingCharacterDie : public FlyingActorDamageBase {
    SEAD_RTTI_OVERRIDE(FlyingCharacterDie, FlyingActorDamageBase)
public:
    explicit FlyingCharacterDie(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
