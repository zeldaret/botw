#pragma once

#include "Game/AI/Action/actionCameraEventAnimFlowBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventAnimFlowAbs : public CameraEventAnimFlowBase {
    SEAD_RTTI_OVERRIDE(CameraEventAnimFlowAbs, CameraEventAnimFlowBase)
public:
    explicit CameraEventAnimFlowAbs(const InitArg& arg);

protected:
};

}  // namespace uking::action
