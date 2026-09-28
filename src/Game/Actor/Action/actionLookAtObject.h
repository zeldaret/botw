#pragma once

#include "Game/Actor/Action/actionTurnAndLookToObjBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LookAtObject : public TurnAndLookToObjBase {
    SEAD_RTTI_OVERRIDE(LookAtObject, TurnAndLookToObjBase)
public:
    explicit LookAtObject(const InitArg& arg);
    ~LookAtObject() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
