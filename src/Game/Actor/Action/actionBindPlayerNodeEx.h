#pragma once

#include "Game/Actor/Action/actionBindPlayerNodeBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BindPlayerNodeEx : public BindPlayerNodeBase {
    SEAD_RTTI_OVERRIDE(BindPlayerNodeEx, BindPlayerNodeBase)
public:
    explicit BindPlayerNodeEx(const InitArg& arg);

protected:
};

}  // namespace uking::action
