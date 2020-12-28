#pragma once

#include "Game/AI/Action/actionCameraLockOnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraMagneCatch : public CameraLockOnBase {
    SEAD_RTTI_OVERRIDE(CameraMagneCatch, CameraLockOnBase)
public:
    explicit CameraMagneCatch(const InitArg& arg);
    ~CameraMagneCatch() override;

protected:
};

}  // namespace uking::action
