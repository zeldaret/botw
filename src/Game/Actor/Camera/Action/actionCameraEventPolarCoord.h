#pragma once

#include "Game/Actor/Camera/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventPolarCoord : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventPolarCoord, CameraEvent)
public:
    explicit CameraEventPolarCoord(const InitArg& arg);

protected:
};

}  // namespace uking::action
