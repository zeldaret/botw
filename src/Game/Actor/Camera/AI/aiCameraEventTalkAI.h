#pragma once

#include "Game/Actor/Camera/AI/aiCameraEventTalk.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraEventTalkAI : public CameraEventTalk {
    SEAD_RTTI_OVERRIDE(CameraEventTalkAI, CameraEventTalk)
public:
    explicit CameraEventTalkAI(const InitArg& arg);

protected:
};

}  // namespace uking::ai
