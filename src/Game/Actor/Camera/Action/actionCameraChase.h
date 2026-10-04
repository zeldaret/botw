#pragma once

#include "Game/Actor/Camera/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraChase : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraChase, CameraAction)
public:
    explicit CameraChase(const InitArg& arg);
    ~CameraChase() override;

protected:
};

}  // namespace uking::action
