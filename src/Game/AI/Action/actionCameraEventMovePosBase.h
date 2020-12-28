#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventMovePosBase : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventMovePosBase, CameraEvent)
public:
    explicit CameraEventMovePosBase(const InitArg& arg);
    ~CameraEventMovePosBase() override;

protected:
};

}  // namespace uking::action
