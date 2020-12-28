#pragma once

#include "Game/AI/Action/actionCameraLockOnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraLockOn : public CameraLockOnBase {
    SEAD_RTTI_OVERRIDE(CameraLockOn, CameraLockOnBase)
public:
    explicit CameraLockOn(const InitArg& arg);

protected:
};

}  // namespace uking::action
