#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraShieldSurfing : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraShieldSurfing, CameraAction)
public:
    explicit CameraShieldSurfing(const InitArg& arg);
    ~CameraShieldSurfing() override;

protected:
};

}  // namespace uking::action
