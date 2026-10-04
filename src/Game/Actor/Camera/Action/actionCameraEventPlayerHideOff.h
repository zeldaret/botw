#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventPlayerHideOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraEventPlayerHideOff, ksys::act::ai::Action)
public:
    explicit CameraEventPlayerHideOff(const InitArg& arg);

protected:
};

}  // namespace uking::action
