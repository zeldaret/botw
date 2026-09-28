#pragma once

#include "Game/Actor/Action/actionTurnAndLookToObjBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerLookAtObject : public TurnAndLookToObjBase {
    SEAD_RTTI_OVERRIDE(PlayerLookAtObject, TurnAndLookToObjBase)
public:
    explicit PlayerLookAtObject(const InitArg& arg);
    ~PlayerLookAtObject() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
