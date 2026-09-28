#pragma once

#include "Game/Actor/Action/actionGrab.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SimpleGrabBase : public Grab {
    SEAD_RTTI_OVERRIDE(SimpleGrabBase, Grab)
public:
    explicit SimpleGrabBase(const InitArg& arg);
    ~SimpleGrabBase() override;

    void loadParams_() override;

protected:
};

}  // namespace uking::action
