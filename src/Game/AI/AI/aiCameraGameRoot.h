#pragma once

#include "Game/AI/AI/aiCameraAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraGameRoot : public CameraAI {
    SEAD_RTTI_OVERRIDE(CameraGameRoot, CameraAI)
public:
    explicit CameraGameRoot(const InitArg& arg);

protected:
};

}  // namespace uking::ai
