#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Msg2CameraResetNoConnect : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Msg2CameraResetNoConnect, ksys::act::ai::Action)
public:
    explicit Msg2CameraResetNoConnect(const InitArg& arg);

protected:
};

}  // namespace uking::action
