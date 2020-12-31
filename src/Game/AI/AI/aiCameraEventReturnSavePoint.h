#pragma once

#include "Game/AI/AI/aiCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraEventReturnSavePoint : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventReturnSavePoint, CameraEvent)
public:
    explicit CameraEventReturnSavePoint(const InitArg& arg);

protected:
};

}  // namespace uking::ai
