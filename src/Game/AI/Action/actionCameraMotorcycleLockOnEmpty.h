#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraMotorcycleLockOnEmpty : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraMotorcycleLockOnEmpty, CameraAction)
public:
    explicit CameraMotorcycleLockOnEmpty(const InitArg& arg);

protected:
};

}  // namespace uking::action
