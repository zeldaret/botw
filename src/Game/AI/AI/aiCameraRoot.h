#pragma once

#include "Game/AI/AI/aiCameraAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraRoot : public CameraAI {
    SEAD_RTTI_OVERRIDE(CameraRoot, CameraAI)
public:
    explicit CameraRoot(const InitArg& arg);
    ~CameraRoot() override;

protected:
};

}  // namespace uking::ai
