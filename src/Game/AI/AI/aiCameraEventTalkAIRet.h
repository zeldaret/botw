#pragma once

#include "Game/AI/AI/aiCameraEventTalk.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraEventTalkAIRet : public CameraEventTalk {
    SEAD_RTTI_OVERRIDE(CameraEventTalkAIRet, CameraEventTalk)
public:
    explicit CameraEventTalkAIRet(const InitArg& arg);

protected:
};

}  // namespace uking::ai
