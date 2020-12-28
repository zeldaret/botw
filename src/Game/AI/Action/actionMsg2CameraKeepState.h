#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Msg2CameraKeepState : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Msg2CameraKeepState, ksys::act::ai::Action)
public:
    explicit Msg2CameraKeepState(const InitArg& arg);

protected:
};

}  // namespace uking::action
