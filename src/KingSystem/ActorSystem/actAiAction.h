#pragma once

#include "KingSystem/ActorSystem/actAiClass.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act::ai {

class Action : public ActionBase {
public:
    Action(const ClassArg& arg);

    virtual void enter() {}
    virtual void loadParams() {}
};
KSYS_CHECK_SIZE_NX150(Action, 0x20);

}  // namespace ksys::act::ai
