#pragma once

#include "Game/AI/Action/actionCameraEventMovePosBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventMovePos : public CameraEventMovePosBase {
    SEAD_RTTI_OVERRIDE(CameraEventMovePos, CameraEventMovePosBase)
public:
    explicit CameraEventMovePos(const InitArg& arg);

protected:
};

}  // namespace uking::action
