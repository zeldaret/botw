#pragma once

#include "Game/AI/Action/actionCameraEventAnimBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventAnimFlowBase : public CameraEventAnimBase {
    SEAD_RTTI_OVERRIDE(CameraEventAnimFlowBase, CameraEventAnimBase)
public:
    explicit CameraEventAnimFlowBase(const InitArg& arg);
    ~CameraEventAnimFlowBase() override;

protected:
};

}  // namespace uking::action
