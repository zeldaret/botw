#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraWakeboard : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraWakeboard, CameraAction)
public:
    explicit CameraWakeboard(const InitArg& arg);
    ~CameraWakeboard() override;

protected:
};

}  // namespace uking::action
