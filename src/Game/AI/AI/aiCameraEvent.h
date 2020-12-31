#pragma once

#include "Game/AI/AI/aiCameraAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraEvent : public CameraAI {
    SEAD_RTTI_OVERRIDE(CameraEvent, CameraAI)
public:
    explicit CameraEvent(const InitArg& arg);

protected:
};

}  // namespace uking::ai
