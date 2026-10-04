#pragma once

#include "Game/Actor/Camera/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventAnimBase : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventAnimBase, CameraEvent)
public:
    explicit CameraEventAnimBase(const InitArg& arg);
    ~CameraEventAnimBase() override;

protected:
};

}  // namespace uking::action
