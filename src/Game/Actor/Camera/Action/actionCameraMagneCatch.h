#pragma once

#include "Game/Actor/Camera/Action/actionCameraTrackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraMagneCatch : public CameraTrackBase {
    SEAD_RTTI_OVERRIDE(CameraMagneCatch, CameraTrackBase)
public:
    explicit CameraMagneCatch(const InitArg& arg);
    ~CameraMagneCatch() override;

protected:
};

}  // namespace uking::action
