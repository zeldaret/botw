#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraAiming : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraAiming, CameraAction)
public:
    explicit CameraAiming(const InitArg& arg);
    ~CameraAiming() override;

protected:
};

}  // namespace uking::action
