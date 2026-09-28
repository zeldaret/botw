#pragma once

#include "Game/Actor/Camera/Action/actionCameraTrackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraLockOn : public CameraTrackBase {
    SEAD_RTTI_OVERRIDE(CameraLockOn, CameraTrackBase)
public:
    explicit CameraLockOn(const InitArg& arg);

protected:
};

}  // namespace uking::action
