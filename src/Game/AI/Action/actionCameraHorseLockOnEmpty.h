#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraHorseLockOnEmpty : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraHorseLockOnEmpty, CameraAction)
public:
    explicit CameraHorseLockOnEmpty(const InitArg& arg);
    ~CameraHorseLockOnEmpty() override;

protected:
};

}  // namespace uking::action
