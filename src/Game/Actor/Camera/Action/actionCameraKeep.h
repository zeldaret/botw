#pragma once

#include "Game/Actor/Camera/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraKeep : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraKeep, CameraAction)
public:
    explicit CameraKeep(const InitArg& arg);

protected:
};

}  // namespace uking::action
