#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraRevolve : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraRevolve, CameraAction)
public:
    explicit CameraRevolve(const InitArg& arg);

protected:
};

}  // namespace uking::action
