#pragma once

#include "Game/AI/Action/actionCameraEventLookBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventLookDirect : public CameraEventLookBase {
    SEAD_RTTI_OVERRIDE(CameraEventLookDirect, CameraEventLookBase)
public:
    explicit CameraEventLookDirect(const InitArg& arg);

protected:
};

}  // namespace uking::action
