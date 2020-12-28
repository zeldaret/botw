#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventTalkManualCtrlBase : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventTalkManualCtrlBase, CameraEvent)
public:
    explicit CameraEventTalkManualCtrlBase(const InitArg& arg);
    ~CameraEventTalkManualCtrlBase() override;

protected:
};

}  // namespace uking::action
