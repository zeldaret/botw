#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraAiming2 : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraAiming2, CameraAction)
public:
    explicit CameraAiming2(const InitArg& arg);
    ~CameraAiming2() override;

protected:
};

}  // namespace uking::action
