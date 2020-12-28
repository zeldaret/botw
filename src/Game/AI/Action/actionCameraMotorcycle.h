#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraMotorcycle : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraMotorcycle, CameraAction)
public:
    explicit CameraMotorcycle(const InitArg& arg);
    ~CameraMotorcycle() override;

protected:
};

}  // namespace uking::action
