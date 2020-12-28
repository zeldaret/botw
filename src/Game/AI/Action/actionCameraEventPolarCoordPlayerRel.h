#pragma once

#include "Game/AI/Action/actionCameraEventPolarCoordPlayer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventPolarCoordPlayerRel : public CameraEventPolarCoordPlayer {
    SEAD_RTTI_OVERRIDE(CameraEventPolarCoordPlayerRel, CameraEventPolarCoordPlayer)
public:
    explicit CameraEventPolarCoordPlayerRel(const InitArg& arg);
    ~CameraEventPolarCoordPlayerRel() override;

protected:
};

}  // namespace uking::action
