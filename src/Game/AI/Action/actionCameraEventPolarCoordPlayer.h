#pragma once

#include "Game/AI/Action/actionCameraEventPolarCoord.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventPolarCoordPlayer : public CameraEventPolarCoord {
    SEAD_RTTI_OVERRIDE(CameraEventPolarCoordPlayer, CameraEventPolarCoord)
public:
    explicit CameraEventPolarCoordPlayer(const InitArg& arg);
    ~CameraEventPolarCoordPlayer() override;

protected:
};

}  // namespace uking::action
