#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraLockOnAimingAt : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraLockOnAimingAt, CameraAction)
public:
    explicit CameraLockOnAimingAt(const InitArg& arg);
    ~CameraLockOnAimingAt() override;

protected:
};

}  // namespace uking::action
