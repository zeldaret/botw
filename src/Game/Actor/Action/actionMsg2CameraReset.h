#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Msg2CameraReset : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Msg2CameraReset, ksys::act::ai::Action)
public:
    explicit Msg2CameraReset(const InitArg& arg);

protected:
};

}  // namespace uking::action
