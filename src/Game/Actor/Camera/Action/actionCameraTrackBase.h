#pragma once

#include "Game/Actor/Camera/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraTrackBase : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraTrackBase, CameraAction)
public:
    explicit CameraTrackBase(const InitArg& arg);
    ~CameraTrackBase() override;

protected:
};

}  // namespace uking::action
