#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraWaterfallClimb : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraWaterfallClimb, CameraAction)
public:
    explicit CameraWaterfallClimb(const InitArg& arg);
    ~CameraWaterfallClimb() override;

protected:
};

}  // namespace uking::action
