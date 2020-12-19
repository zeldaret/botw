#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act::ai {

class Action : public ActionBase {
    SEAD_RTTI_OVERRIDE(Action, ActionBase)
public:
    explicit Action(const InitArg& arg);

    void calc() override;
    ActionType getType() const override { return ActionType::Action; }

protected:
    virtual void calc_() {}
};
KSYS_CHECK_SIZE_NX150(Action, 0x20);

class Actions {
public:
    Actions();
    ~Actions();

    void finalize();

    sead::Buffer<Action*> classes;
    // TODO: rename
    sead::Buffer<Action*> x;
    // TODO: rename
    sead::Buffer<Action*> y;
};

}  // namespace ksys::act::ai
