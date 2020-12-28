#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventLookBase : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventLookBase, CameraEvent)
public:
    explicit CameraEventLookBase(const InitArg& arg);
    ~CameraEventLookBase() override;

protected:
};

}  // namespace uking::action
