#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraRumbleStop : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraRumbleStop, ksys::act::ai::Action)
public:
    explicit CameraRumbleStop(const InitArg& arg);

    void loadParams_() override;

protected:
    // aitree_variable at offset 0x20
    int* mCamVibId_a{};
};

}  // namespace uking::action
