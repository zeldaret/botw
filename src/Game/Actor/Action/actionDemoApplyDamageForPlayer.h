#pragma once

#include "Game/Actor/Action/actionDemoApplyDamageBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoApplyDamageForPlayer : public DemoApplyDamageBase {
    SEAD_RTTI_OVERRIDE(DemoApplyDamageForPlayer, DemoApplyDamageBase)
public:
    explicit DemoApplyDamageForPlayer(const InitArg& arg);
    ~DemoApplyDamageForPlayer() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
