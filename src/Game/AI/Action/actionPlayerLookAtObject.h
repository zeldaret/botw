#pragma once

#include "Game/AI/Action/actionLookAtObjectBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerLookAtObject : public LookAtObjectBase {
    SEAD_RTTI_OVERRIDE(PlayerLookAtObject, LookAtObjectBase)
public:
    explicit PlayerLookAtObject(const InitArg& arg);
    ~PlayerLookAtObject() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
