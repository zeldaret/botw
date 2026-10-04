#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AirWallAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AirWallAction, ksys::act::ai::Action)
public:
    explicit AirWallAction(const InitArg& arg);

protected:
    void calc_() override;
};

}  // namespace uking::action
