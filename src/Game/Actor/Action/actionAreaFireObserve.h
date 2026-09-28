#pragma once

#include "Game/Actor/Area/Action/actionFireObserveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaFireObserve : public FireObserveBase {
    SEAD_RTTI_OVERRIDE(AreaFireObserve, FireObserveBase)
public:
    explicit AreaFireObserve(const InitArg& arg);

protected:
};

}  // namespace uking::action
