#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Msg2CameraResetInterpolate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Msg2CameraResetInterpolate, ksys::act::ai::Action)
public:
    explicit Msg2CameraResetInterpolate(const InitArg& arg);

    void loadParams_() override;

protected:
    // dynamic2_param at offset 0x20
    float* mInterpolateParam_d{};
};

}  // namespace uking::action
