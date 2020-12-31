#pragma once

#include "Game/AI/AI/aiCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraEventTalk : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventTalk, CameraEvent)
public:
    explicit CameraEventTalk(const InitArg& arg);
    ~CameraEventTalk() override;

protected:
};

}  // namespace uking::ai
