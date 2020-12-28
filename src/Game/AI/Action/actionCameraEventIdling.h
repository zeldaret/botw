#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventIdling : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventIdling, CameraEvent)
public:
    explicit CameraEventIdling(const InitArg& arg);

protected:
};

}  // namespace uking::action
