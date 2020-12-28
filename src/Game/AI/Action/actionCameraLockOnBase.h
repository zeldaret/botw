#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraLockOnBase : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraLockOnBase, CameraAction)
public:
    explicit CameraLockOnBase(const InitArg& arg);
    ~CameraLockOnBase() override;

protected:
};

}  // namespace uking::action
