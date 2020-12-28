#pragma once

#include "Game/AI/Action/actionFlyingCharacterDamageBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyingCharacterDamage : public FlyingCharacterDamageBase {
    SEAD_RTTI_OVERRIDE(FlyingCharacterDamage, FlyingCharacterDamageBase)
public:
    explicit FlyingCharacterDamage(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
