#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventMove : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventMove, CameraEvent)
public:
    explicit CameraEventMove(const InitArg& arg);
    ~CameraEventMove() override;

protected:
};

}  // namespace uking::action
