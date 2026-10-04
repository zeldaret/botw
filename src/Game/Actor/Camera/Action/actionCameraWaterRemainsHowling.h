#pragma once

#include "Game/Actor/Camera/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraWaterRemainsHowling : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraWaterRemainsHowling, CameraAction)
public:
    explicit CameraWaterRemainsHowling(const InitArg& arg);
    ~CameraWaterRemainsHowling() override;

protected:
};

}  // namespace uking::action
