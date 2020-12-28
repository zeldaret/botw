#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventMultiTalk : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventMultiTalk, CameraEvent)
public:
    explicit CameraEventMultiTalk(const InitArg& arg);
    ~CameraEventMultiTalk() override;

protected:
};

}  // namespace uking::action
