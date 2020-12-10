#pragma once

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

}  // namespace ksys::act::ai
