#pragma once

#include "Game/Actor/Camera/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraTail : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraTail, CameraAction)
public:
    explicit CameraTail(const InitArg& arg);
    ~CameraTail() override;

protected:
};

}  // namespace uking::action
