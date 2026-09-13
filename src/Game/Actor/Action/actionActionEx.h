#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ActionEx : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ActionEx, ksys::act::ai::Action)
public:
    explicit ActionEx(const InitArg& arg);

protected:
};

}  // namespace uking::action
