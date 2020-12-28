#pragma once

#include "Game/AI/Action/actionLookAtObjectBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LookAtObject : public LookAtObjectBase {
    SEAD_RTTI_OVERRIDE(LookAtObject, LookAtObjectBase)
public:
    explicit LookAtObject(const InitArg& arg);
    ~LookAtObject() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
