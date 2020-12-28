#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraClimbObj : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraClimbObj, CameraAction)
public:
    explicit CameraClimbObj(const InitArg& arg);
    ~CameraClimbObj() override;

protected:
};

}  // namespace uking::action
