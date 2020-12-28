#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEvent : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraEvent, CameraAction)
public:
    explicit CameraEvent(const InitArg& arg);

protected:
};

}  // namespace uking::action
