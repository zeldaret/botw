#pragma once

#include "Game/Actor/Camera/Action/actionCameraEventAnimFlowBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventAnimFlow : public CameraEventAnimFlowBase {
    SEAD_RTTI_OVERRIDE(CameraEventAnimFlow, CameraEventAnimFlowBase)
public:
    explicit CameraEventAnimFlow(const InitArg& arg);
    ~CameraEventAnimFlow() override;

protected:
};

}  // namespace uking::action
