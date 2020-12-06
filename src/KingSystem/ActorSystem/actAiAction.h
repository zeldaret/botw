#pragma once

#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act::ai {

class Action : public ActionBase {
public:
    explicit Action(const InitArg& arg);

    virtual void enter() {}
    virtual void loadParams() {}
    virtual void oneShot() {}

    bool isAction() override;
};
KSYS_CHECK_SIZE_NX150(Action, 0x20);

}  // namespace ksys::act::ai
