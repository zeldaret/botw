#pragma once

#include "Game/AI/Action/actionGrab.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SimpleGrabWithASBase : public Grab {
    SEAD_RTTI_OVERRIDE(SimpleGrabWithASBase, Grab)
public:
    explicit SimpleGrabWithASBase(const InitArg& arg);
    ~SimpleGrabWithASBase() override;

    void loadParams_() override;

protected:
};

}  // namespace uking::action
