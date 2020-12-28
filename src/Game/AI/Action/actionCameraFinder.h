#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraFinder : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraFinder, CameraAction)
public:
    explicit CameraFinder(const InitArg& arg);
    ~CameraFinder() override;

protected:
};

}  // namespace uking::action
