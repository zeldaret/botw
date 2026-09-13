#pragma once

#include "Game/Actor/Camera/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventTurn : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventTurn, CameraEvent)
public:
    explicit CameraEventTurn(const InitArg& arg);
    ~CameraEventTurn() override;

protected:
};

}  // namespace uking::action
