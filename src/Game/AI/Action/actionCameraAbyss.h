#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraAbyss : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraAbyss, CameraAction)
public:
    explicit CameraAbyss(const InitArg& arg);

protected:
};

}  // namespace uking::action
