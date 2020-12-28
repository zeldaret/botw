#pragma once

#include "Game/AI/Action/actionApplyDamageForPlayer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoApplyDamageForPlayer : public ApplyDamageForPlayer {
    SEAD_RTTI_OVERRIDE(DemoApplyDamageForPlayer, ApplyDamageForPlayer)
public:
    explicit DemoApplyDamageForPlayer(const InitArg& arg);
    ~DemoApplyDamageForPlayer() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
