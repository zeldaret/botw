#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventPlayerHideOn : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraEventPlayerHideOn, ksys::act::ai::Action)
public:
    explicit CameraEventPlayerHideOn(const InitArg& arg);

protected:
};

}  // namespace uking::action
