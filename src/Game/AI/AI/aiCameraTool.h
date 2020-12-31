#pragma once

#include "Game/AI/AI/aiCameraAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraTool : public CameraAI {
    SEAD_RTTI_OVERRIDE(CameraTool, CameraAI)
public:
    explicit CameraTool(const InitArg& arg);
    ~CameraTool() override;

protected:
};

}  // namespace uking::ai
