#pragma once

#include "Game/AI/Action/actionAreaFireObserveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaFireObserve : public AreaFireObserveBase {
    SEAD_RTTI_OVERRIDE(AreaFireObserve, AreaFireObserveBase)
public:
    explicit AreaFireObserve(const InitArg& arg);

protected:
};

}  // namespace uking::action
