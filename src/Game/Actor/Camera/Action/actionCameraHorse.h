#pragma once

#include "Game/Actor/Camera/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraHorse : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraHorse, CameraAction)
public:
    explicit CameraHorse(const InitArg& arg);
    ~CameraHorse() override;

protected:
};

}  // namespace uking::action
