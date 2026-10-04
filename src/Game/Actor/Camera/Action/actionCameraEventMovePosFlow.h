#pragma once

#include "Game/Actor/Camera/Action/actionCameraEventMovePosBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventMovePosFlow : public CameraEventMovePosBase {
    SEAD_RTTI_OVERRIDE(CameraEventMovePosFlow, CameraEventMovePosBase)
public:
    explicit CameraEventMovePosFlow(const InitArg& arg);

protected:
};

}  // namespace uking::action
