#pragma once

#include "Game/AI/Action/actionCameraEventAnimBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventAnim : public CameraEventAnimBase {
    SEAD_RTTI_OVERRIDE(CameraEventAnim, CameraEventAnimBase)
public:
    explicit CameraEventAnim(const InitArg& arg);
    ~CameraEventAnim() override;

protected:
};

}  // namespace uking::action
