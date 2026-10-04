#pragma once

#include "Game/Actor/Camera/Action/actionCameraEventTalkManualCtrlBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventTalkManualCtrl : public CameraEventTalkManualCtrlBase {
    SEAD_RTTI_OVERRIDE(CameraEventTalkManualCtrl, CameraEventTalkManualCtrlBase)
public:
    explicit CameraEventTalkManualCtrl(const InitArg& arg);

protected:
};

}  // namespace uking::action
