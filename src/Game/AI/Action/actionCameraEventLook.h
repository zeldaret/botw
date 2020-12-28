#pragma once

#include "Game/AI/Action/actionCameraEventLookBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventLook : public CameraEventLookBase {
    SEAD_RTTI_OVERRIDE(CameraEventLook, CameraEventLookBase)
public:
    explicit CameraEventLook(const InitArg& arg);
    ~CameraEventLook() override;

protected:
};

}  // namespace uking::action
