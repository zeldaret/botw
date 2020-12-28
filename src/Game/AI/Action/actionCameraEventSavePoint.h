#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventSavePoint : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraEventSavePoint, CameraAction)
public:
    explicit CameraEventSavePoint(const InitArg& arg);

protected:
};

}  // namespace uking::action
