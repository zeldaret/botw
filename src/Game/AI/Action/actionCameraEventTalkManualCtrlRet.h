#pragma once

#include "Game/AI/Action/actionCameraEventTalkManualCtrlBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventTalkManualCtrlRet : public CameraEventTalkManualCtrlBase {
    SEAD_RTTI_OVERRIDE(CameraEventTalkManualCtrlRet, CameraEventTalkManualCtrlBase)
public:
    explicit CameraEventTalkManualCtrlRet(const InitArg& arg);

protected:
};

}  // namespace uking::action
