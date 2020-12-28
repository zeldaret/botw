#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventGameOver : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventGameOver, CameraEvent)
public:
    explicit CameraEventGameOver(const InitArg& arg);
    ~CameraEventGameOver() override;

protected:
};

}  // namespace uking::action
