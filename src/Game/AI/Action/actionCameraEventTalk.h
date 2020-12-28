#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventTalk : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventTalk, CameraEvent)
public:
    explicit CameraEventTalk(const InitArg& arg);
    ~CameraEventTalk() override;

protected:
};

}  // namespace uking::action
